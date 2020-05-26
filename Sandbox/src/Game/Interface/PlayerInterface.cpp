#include "PlayerInterface.h"

PlayerInterface::PlayerInterface(std::shared_ptr<Player> player, std::shared_ptr<MessageLog> messageLog, std::shared_ptr<Map> map, std::shared_ptr<NpcHandler> npcHandler)
	: mPlayer(player), mMessageLog(messageLog), mMap(map),
	mCommandManager(mPlayer, mMap, mMessageLog), mGameGrid(mMap, npcHandler)
{
	mMessageLog->Translate(Square::Vector2(0.0f, Square::Graphics::SCREEN_HEIGHT));

	mMenuTabsInterface = new MenuTabsInterface(mPlayer);

	/*
	mMessageLog->AddMessage("2. This is a test message.", {128, 0, 0, 255 });
	mMessageLog->AddMessage("3. This is a test message.", { 0, 128, 0, 255 });
	mMessageLog->AddMessage("4. This is a test message.", { 0, 0, 128, 255 });
	mMessageLog->AddMessage("5. This is a test message.", { 128, 128, 128, 255 });
	mMessageLog->AddMessage("6. This is a test message.", { 128, 0, 128, 255 });
	mMessageLog->AddMessage("7. This is a test message.", { 0, 128, 128, 255 });
	*/

	mCommand = "";

	mWaitingForInteraction = false;

	mHoverText = "";
	mHoverSprite = nullptr;

	mActionsMenu = nullptr;

	mTargetObject = nullptr;
}

PlayerInterface::~PlayerInterface()
{
	delete mMenuTabsInterface;

	delete mHoverSprite;

	delete mActionsMenu;
}

void PlayerInterface::Reset()
{
	mCommand.clear();

	mWaitingForInteraction = false;

	mHoverText = "";

	delete mHoverSprite;
	mHoverSprite = nullptr;

	delete mActionsMenu;
	mActionsMenu = nullptr;

	mTargetObject = nullptr;
}

void PlayerInterface::SetHoverText()
{
	Square::Vector2 pos = Square::InputHandler::Instance().MousePos();

	std::string hoverText = "";

	if (mMenuTabsInterface->Tab("Inventory")->Active())
	{
		if (!mMenuTabsInterface->Tab("Inventory")->MenuOpened() && mActionsMenu == nullptr)
		{
			if (mWaitingForInteraction)
			{
				hoverText += "Use " + mPlayer->Inventory().GetItem(mPlayer->Inventory().ActiveSlot())->Name() + " -> ";
			}

			if (Item* item = dynamic_cast<Item*>(mMenuTabsInterface->Tab("Inventory")->GetSlot(pos, false).get()))
			{
				if (mWaitingForInteraction)
				{
					hoverText += item->Name();
				}
				else
					hoverText += item->InventoryActions().front() + " " + item->Name();
			}
		}
	}
	else if (mMenuTabsInterface->Tab("Gear")->Active())
	{
		if (!mMenuTabsInterface->Tab("Gear")->MenuOpened() && mActionsMenu == nullptr)
		{
			if (Item* item = dynamic_cast<Item*>(mMenuTabsInterface->Tab("Gear")->GetSlot(pos).get()))
				hoverText += "Unequip " + item->Name();
		}
	}
	else if (mMenuTabsInterface->Tab("Prayer")->Active())
	{
		if (!mMenuTabsInterface->Tab("Prayer")->MenuOpened() && mActionsMenu == nullptr)
		{
			if (Aura* aura = dynamic_cast<Aura*>(mMenuTabsInterface->Tab("Prayer")->GetSlot(pos).get()))
				hoverText += (aura->Activated() ? "Deactivate " : "Activate ") + aura->Name();
		}
	}
	else if (mMenuTabsInterface->Tab("Magic")->Active())
	{
		if (!mMenuTabsInterface->Tab("Magic")->MenuOpened() && mActionsMenu == nullptr)
		{
			if (mWaitingForInteraction)
			{
				hoverText += "Cast " + mPlayer->SpellBook().Spells()[mPlayer->SpellBook().ActiveSpell()]->Name() + " -> ";
			}

			if (Spell* spell = dynamic_cast<Spell*>(mMenuTabsInterface->Tab("Magic")->GetSlot(pos).get()))
			{
				if (!mWaitingForInteraction)
				{
					hoverText += "Cast " + spell->Name();
				}
			}
		}
	}
	else if (mMenuTabsInterface->Tab("Stats")->Active())
	{
		if (!mMenuTabsInterface->Tab("Stats")->MenuOpened() && mActionsMenu == nullptr)
		{
			if (Skill* skill = dynamic_cast<Skill*>(mMenuTabsInterface->Tab("Stats")->GetSlot(pos).get()))
				hoverText += skill->SkillName() + " Skill";
		}
	}
	
	if (hoverText.empty() && !mMenuTabsInterface->ContainsClick() && (!mMessageLog->ContainsClick() || mActionsMenu))
	{
		if (mActionsMenu == nullptr)
		{
			Square::Vector2 target;
			target.x = (Square::InputHandler::Instance().MousePos().x + Square::Graphics::Instance().Camera().x);
			target.y = (Square::InputHandler::Instance().MousePos().y + Square::Graphics::Instance().Camera().y);

			if (mGameGrid.GetGridObjects(target, mPlayer->MapPosition().z).size())
				hoverText += mGameGrid.GetGridObjects(target, mPlayer->MapPosition().z).front()->Command();
		}
	}

	if (mHoverText != hoverText)
	{
		mHoverText = hoverText;

		delete mHoverSprite;
		mHoverSprite = nullptr;
		
		if (!mHoverText.empty())
		{
			mHoverSprite = new Square::Text(mHoverText, "Font/VeraMono.ttf", 16, { 255, 140, 0, 255 });
			mHoverSprite->Parent(this);
			mHoverSprite->Pos(mHoverSprite->ScaledDimensions() * 0.5f + 4.0f);
		}
	}
}

void PlayerInterface::HandleUse()
{
	if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::left))
	{
		if (mActionsMenu)
		{
			mActionsMenu->Active(false);
			if (!mActionsMenu->Action().empty())
				mPlayer->Target(mTargetObject);
		}
		else if (mMenuTabsInterface->Tab("Inventory")->ContainsClick())
		{
			mPlayer->Target(mMenuTabsInterface->Tab("Inventory")->GetSlot(Square::InputHandler::Instance().MousePos(), false));
		}

		mWaitingForInteraction = false;
		mMenuTabsInterface->Reset();
	}
	else if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::right))
	{
		if (mActionsMenu == nullptr)
		{
			std::string activeItem = mPlayer->Inventory().GetItem(mPlayer->Inventory().ActiveSlot())->Name();
			std::string targetObject = "";

			if (mMenuTabsInterface->Tab("Inventory")->ContainsClick())
			{
				if (std::shared_ptr<Item> item = std::dynamic_pointer_cast<Item>(mMenuTabsInterface->Tab("Inventory")->GetSlot(Square::InputHandler::Instance().MousePos(), false)))
				{
					targetObject = item->Name();
					mTargetObject = item;
				}
			}

			mActionsMenu = new ActionsMenu("Options", { mHoverText }, Square::InputHandler::Instance().MousePos());
		}
	}
}

void PlayerInterface::HandleCast()
{
	if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::left))
	{
		if (mActionsMenu)
		{
			mActionsMenu->Active(false);
			if (!mActionsMenu->Action().empty())
				mPlayer->Target(mTargetObject);
		}

		mWaitingForInteraction = false;
		mMenuTabsInterface->Reset();
	}
	else if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::right))
	{
		if (mActionsMenu == nullptr)
		{
			std::string activeItem = mPlayer->SpellBook().Spells()[mPlayer->SpellBook().ActiveSpell()]->Name();
			std::string targetObject = "";

			mActionsMenu = new ActionsMenu("Options", { mHoverText }, Square::InputHandler::Instance().MousePos());
		}
	}
}

void PlayerInterface::HandleActionsMenu()
{
	if (mActionsMenu)
	{
		mActionsMenu->Update();

		if (!mActionsMenu->Active())
		{
			delete mActionsMenu;
			mActionsMenu = nullptr;

			mTargetObject = nullptr;
		}
	}
}

void PlayerInterface::HandleInteraction()
{
	Square::Vector2 target;
	target.x = (Square::InputHandler::Instance().MousePos().x + Square::Graphics::Instance().Camera().x);
	target.y = (Square::InputHandler::Instance().MousePos().y + Square::Graphics::Instance().Camera().y);

	if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::left))
	{
		if (mActionsMenu)
		{
			mActionsMenu->Active(false);
			if (!mActionsMenu->Action().empty())
			{
				mCommand = mActionsMenu->Action();
				mPlayer->Target(mActionsMenu->Object());
			}
		}
		else if (!mWaitingForInteraction)
		{
			if (mGameGrid.GetGridObjects(target, mPlayer->MapPosition().z).size())
			{
				mCommand = Trim(Substring(mGameGrid.GetGridObjects(target, mPlayer->MapPosition().z).front()->Command(), "->"));
				mPlayer->Target(mGameGrid.GetGridObjects(target, mPlayer->MapPosition().z).front()->Target());
			}
		}
	}
	else if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::right))
	{
		if (mGameGrid.GetGridObjects(target, mPlayer->MapPosition().z).size())
		{
			mActionsMenu = new ActionsMenu("Options", mGameGrid.GetGridObjects(target, mPlayer->MapPosition().z), Square::InputHandler::Instance().MousePos());
		}
	}
}

void PlayerInterface::Update()
{
	bool menuOpened = (mActionsMenu != nullptr);

	if (Square::InputHandler::Instance().KeyPressed(SDL_SCANCODE_Z))
		mMessageLog->Active(!mMessageLog->Active());
	mMessageLog->Update();

	if (mMenuTabsInterface->WaitingForInteraction())
	{
		if (mCommand == "Use")
			HandleUse();
		else if (mCommand == "Cast")
			HandleCast();
	}
	else if (!mCommand.empty())
	{
		mCommandManager.Invoke(mCommand);
		mCommand.clear();
	}

	SetHoverText();

	HandleActionsMenu();

	if (!mMenuTabsInterface->ContainsClick() && (!mMessageLog->ContainsClick() || mActionsMenu) && mCommand.empty())
		HandleInteraction();

	mMenuTabsInterface->Update();

	if (!mMenuTabsInterface->Command().empty())
	{
		mCommand = mMenuTabsInterface->Command();
		mWaitingForInteraction = mMenuTabsInterface->WaitingForInteraction();
	}
}

void PlayerInterface::Render()
{
	mMenuTabsInterface->Render();
	
	if (mMessageLog->Active())
		mMessageLog->Render();

	if (mHoverSprite) mHoverSprite->Render(true);

	if (mActionsMenu) mActionsMenu->Render();
}
