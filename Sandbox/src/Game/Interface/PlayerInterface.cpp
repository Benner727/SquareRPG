#include "PlayerInterface.h"

PlayerInterface::PlayerInterface(Player& player, Map& map)
	: mPlayer(player), mMap(map), mCommandManager(&mPlayer, &mMap)
{
	mMenuTabsInterface = new MenuTabsInterface(player);

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

void PlayerInterface::HandleMove()
{
	if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::left))
	{
		Point target;
		target.x = (Square::InputHandler::Instance().MousePos().x + Square::Graphics::Instance().Camera().x) / 32.0f;
		target.y = (Square::InputHandler::Instance().MousePos().y + Square::Graphics::Instance().Camera().y) / 32.0f;
		target.z = mPlayer.MapPosition().z;

		mPlayer.Target(mMap.GetTile(target));
		if (!mWaitingForInteraction)
		{
			mCommand = "Move";
		}
	}
}

void PlayerInterface::Update()
{
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

	if (!mMenuTabsInterface->ContainsClick() && mCommand.empty())
		HandleMove();

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

	if (mHoverSprite) mHoverSprite->Render(true);

	if (mActionsMenu) mActionsMenu->Render();
}
