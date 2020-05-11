#include "PlayerInterface.h"

PlayerInterface::PlayerInterface(Player& player, Map& map)
	: mPlayer(player), mMap(map), mCommandManager(&mPlayer, &mMap), mGameGrid(&mMap)
{
	mMenuTabsInterface = new MenuTabsInterface(player);

	mMessageLog = new MessageLog(50, 8, "Font/VeraMono.ttf", 14, { 15.0f, -15.0f });
	mMessageLog->Translate(Square::Vector2(0.0f, Square::Graphics::SCREEN_HEIGHT));

	mMessageLog->AddMessage("1.Thisisatestmessage.Thisisatestmessage.Thisisatestmessage.Thisisatestmessage.Thisisatestmessage.Thisisatestmessage.", { 0, 0, 0, 255 });
	mMessageLog->AddMessage("2. This is a test message.", { 178, 0, 0, 255 });
	mMessageLog->AddMessage("3. This is a test message.", { 0, 178, 0, 255 });
	mMessageLog->AddMessage("4. This is a test message.", { 0, 0, 178, 255 });
	mMessageLog->AddMessage("5. This is a test message.", { 255, 255, 255, 255 });
	mMessageLog->AddMessage("6. This is a test message.", { 178, 0, 0, 255 });
	mMessageLog->AddMessage("7. This is a test message.", { 0, 178, 0, 255 });

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
	delete mMessageLog;

	delete mHoverSprite;

	delete mActionsMenu;
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
				hoverText += "Use " + mPlayer.Inventory().GetItem(mPlayer.Inventory().ActiveSlot())->Name() + " -> ";
			}

			if (Item* item = dynamic_cast<Item*>(mMenuTabsInterface->Tab("Inventory")->GetSlot(pos, false)))
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
			if (Item* item = dynamic_cast<Item*>(mMenuTabsInterface->Tab("Gear")->GetSlot(pos)))
				hoverText += "Unequip " + item->Name();
		}
	}
	else if (mMenuTabsInterface->Tab("Prayer")->Active())
	{
		if (!mMenuTabsInterface->Tab("Prayer")->MenuOpened() && mActionsMenu == nullptr)
		{
			if (Aura* aura = dynamic_cast<Aura*>(mMenuTabsInterface->Tab("Prayer")->GetSlot(pos)))
				hoverText += (aura->Activated() ? "Deactivate " : "Activate ") + aura->Name();
		}
	}
	else if (mMenuTabsInterface->Tab("Magic")->Active())
	{
		if (!mMenuTabsInterface->Tab("Magic")->MenuOpened() && mActionsMenu == nullptr)
		{
			if (mWaitingForInteraction)
			{
				hoverText += "Cast " + mPlayer.SpellBook().Spells()[mPlayer.SpellBook().ActiveSpell()]->Name() + " -> ";
			}

			if (Spell* spell = dynamic_cast<Spell*>(mMenuTabsInterface->Tab("Magic")->GetSlot(pos)))
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
			if (Skill* skill = dynamic_cast<Skill*>(mMenuTabsInterface->Tab("Stats")->GetSlot(pos)))
				hoverText += skill->SkillName() + " Skill";
		}
	}
	
	if (hoverText.empty() && !mMenuTabsInterface->ContainsClick() && (!mMessageLog->ContainsClick() || mActionsMenu))
	{
		if (mActionsMenu == nullptr)
		{
			Point target;
			target.x = (Square::InputHandler::Instance().MousePos().x + Square::Graphics::Instance().Camera().x) / 32.0f;
			target.y = (Square::InputHandler::Instance().MousePos().y + Square::Graphics::Instance().Camera().y) / 32.0f;
			target.z = mPlayer.MapPosition().z;

			if (mGameGrid.GetGridObjects(target).size())
				hoverText += mGameGrid.GetGridObjects(target).front()->Command();
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
				mPlayer.Target(mTargetObject);
		}
		else if (mMenuTabsInterface->Tab("Inventory")->ContainsClick())
		{
			mPlayer.Target(mMenuTabsInterface->Tab("Inventory")->GetSlot(Square::InputHandler::Instance().MousePos(), false));
		}

		mWaitingForInteraction = false;
		mMenuTabsInterface->Reset();
	}
	else if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::right))
	{
		if (mActionsMenu == nullptr)
		{
			std::string activeItem = mPlayer.Inventory().GetItem(mPlayer.Inventory().ActiveSlot())->Name();
			std::string targetObject = "";

			if (mMenuTabsInterface->Tab("Inventory")->ContainsClick())
			{
				if (Item* item = dynamic_cast<Item*>(mMenuTabsInterface->Tab("Inventory")->GetSlot(Square::InputHandler::Instance().MousePos(), false)))
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
				mPlayer.Target(mTargetObject);
		}

		mWaitingForInteraction = false;
		mMenuTabsInterface->Reset();
	}
	else if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::right))
	{
		if (mActionsMenu == nullptr)
		{
			std::string activeItem = mPlayer.SpellBook().Spells()[mPlayer.SpellBook().ActiveSpell()]->Name();
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
	Point target;
	target.x = (Square::InputHandler::Instance().MousePos().x + Square::Graphics::Instance().Camera().x) / 32.0f;
	target.y = (Square::InputHandler::Instance().MousePos().y + Square::Graphics::Instance().Camera().y) / 32.0f;
	target.z = mPlayer.MapPosition().z;

	if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::left))
	{
		if (mActionsMenu)
		{
			mActionsMenu->Active(false);
			if (!mActionsMenu->Action().empty())
			{
				mCommand = mActionsMenu->Action();
				mPlayer.Target(mActionsMenu->Object());
			}
		}
		else if (!mWaitingForInteraction)
		{
			if (mGameGrid.GetGridObjects(target).size())
			{
				mCommand = Trim(Substring(mGameGrid.GetGridObjects(target).front()->Command(), "->"));
				mPlayer.Target(mGameGrid.GetGridObjects(target).front()->Target());
			}
		}
	}
	else if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::right))
	{
		if (mGameGrid.GetGridObjects(target).size())
		{
			mActionsMenu = new ActionsMenu("Options", mGameGrid.GetGridObjects(target), Square::InputHandler::Instance().MousePos());
		}
	}
}

void PlayerInterface::Update()
{
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
