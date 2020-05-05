#include "PlayerInterface.h"

PlayerInterface::PlayerInterface(Player& player, Map& map)
	: mPlayer(player), mMap(map), mCommandManager(&mPlayer, &mMap)
{
	mWaitingForUse = false;
	mWaitingForCast = false;

	AddButton("Magic");
	AddButton("Prayer");
	AddButton("Gear");
	AddButton("Inventory");
	AddButton("Stats");
	AddButton("Combat");

	mTabs["Inventory"] = new InventoryInterface(mPlayer.Inventory());
	mTabs["Inventory"]->Parent(this);
	mTabs["Inventory"]->Pos(Square::Vector2(Square::Graphics::SCREEN_WIDTH - 208, Square::Graphics::SCREEN_HEIGHT - 256 - mButtons["Inventory"]->Height()));

	mTabs["Gear"] = new GearInterface(mPlayer.Gear());
	mTabs["Gear"]->Parent(this);
	mTabs["Gear"]->Pos(Square::Vector2(Square::Graphics::SCREEN_WIDTH - 208, Square::Graphics::SCREEN_HEIGHT - 256 - mButtons["Gear"]->Height()));
	mTabs["Gear"]->Active(false);

	mTabs["Prayer"] = new PrayerInterface(mPlayer.PrayerBook());
	mTabs["Prayer"]->Parent(this);
	mTabs["Prayer"]->Pos(Square::Vector2(Square::Graphics::SCREEN_WIDTH - 208, Square::Graphics::SCREEN_HEIGHT - 256 - mButtons["Prayer"]->Height()));
	mTabs["Prayer"]->Active(false);

	mTabs["Magic"] = new MagicInterface(mPlayer.SpellBook());
	mTabs["Magic"]->Parent(this);
	mTabs["Magic"]->Pos(Square::Vector2(Square::Graphics::SCREEN_WIDTH - 208, Square::Graphics::SCREEN_HEIGHT - 256 - mButtons["Magic"]->Height()));
	mTabs["Magic"]->Active(false);

	mTabs["Stats"] = new StatsInterface(mPlayer.Skills());
	mTabs["Stats"]->Parent(this);
	mTabs["Stats"]->Pos(Square::Vector2(Square::Graphics::SCREEN_WIDTH - 208, Square::Graphics::SCREEN_HEIGHT - 256 - mButtons["Stats"]->Height()));
	mTabs["Stats"]->Active(false);

	mHoverText = "";
	mHoverSprite = nullptr;

	mActionsMenu = nullptr;

	mTargetObject = nullptr;
}

PlayerInterface::~PlayerInterface()
{
	for (auto button : mButtons)
		delete button.second;

	delete mHoverSprite;

	delete mActionsMenu;
}

void PlayerInterface::AddButton(std::string button)
{
	mButtons[button] = new Button("Graphics/buttonSquare_brown.png");
	mButtons[button]->Parent(this);
	mButtons[button]->Pos(Square::Vector2(Square::Graphics::SCREEN_WIDTH - mButtons[button]->Width() * 0.5f - (mButtons[button]->Width() * (mButtons.size() - 1)), 
		Square::Graphics::SCREEN_HEIGHT - mButtons[button]->Height() * 0.5f));
}

bool PlayerInterface::ContainsClick() const
{
	for (const auto& button : mButtons)
	{
		if (button.second->Pressed())
			return true;
	}

	for (const auto& tab : mTabs)
	{
		if (tab.second->ContainsClick())
		{
			if (tab.second->Active())
				return true;
		}
	}

	return false;
}

void PlayerInterface::HandleButtons()
{
	if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::left))
	{
		for (auto& button : mButtons)
		{
			if (button.second->Pressed())
				SwitchTab(button.first);
		}
	}
}

void PlayerInterface::SwitchTab(std::string key)
{
	for (auto& tab : mTabs)
	{
		if (tab.first == key)
		{
			tab.second->Active(!tab.second->Active());
		}
		else
		{
			tab.second->Active(false);
		}
	}
}

void PlayerInterface::SetHoverText()
{
	Square::Vector2 pos = Square::InputHandler::Instance().MousePos();

	std::string hoverText = "";

	if (mTabs["Inventory"]->Active())
	{
		if (!mTabs["Inventory"]->MenuOpened() && mActionsMenu == nullptr)
		{
			if (mWaitingForUse)
			{
				hoverText += "Use " + mPlayer.Inventory().GetItem(mPlayer.Inventory().ActiveSlot())->Name() + " -> ";
			}

			if (Item* item = dynamic_cast<Item*>(mTabs["Inventory"]->GetSlot(pos, false)))
			{
				if (mWaitingForUse)
				{
					hoverText += item->Name();
				}
				else
					hoverText += item->InventoryActions().front() + " " + item->Name();
			}
		}
	}
	else if (mTabs["Gear"]->Active())
	{
		if (!mTabs["Gear"]->MenuOpened() && mActionsMenu == nullptr)
		{
			if (Item* item = dynamic_cast<Item*>(mTabs["Gear"]->GetSlot(pos)))
				hoverText += "Unequip " + item->Name();
		}
	}
	else if (mTabs["Prayer"]->Active())
	{
		if (!mTabs["Prayer"]->MenuOpened() && mActionsMenu == nullptr)
		{
			if (Aura* aura = dynamic_cast<Aura*>(mTabs["Prayer"]->GetSlot(pos)))
				hoverText += (aura->Activated() ? "Deactivate " : "Activate ") + aura->Name();
		}
	}
	else if (mTabs["Magic"]->Active())
	{
		if (!mTabs["Magic"]->MenuOpened() && mActionsMenu == nullptr)
		{
			if (mWaitingForCast)
			{
				hoverText += "Cast " + mPlayer.SpellBook().Spells()[mPlayer.SpellBook().ActiveSpell()]->Name() + " -> ";
			}

			if (Spell* spell = dynamic_cast<Spell*>(mTabs["Magic"]->GetSlot(pos)))
			{
				if (!mWaitingForCast)
				{
					hoverText += "Cast " + spell->Name();
				}
			}
		}
	}
	else if (mTabs["Stats"]->Active())
	{
		if (!mTabs["Stats"]->MenuOpened() && mActionsMenu == nullptr)
		{
			if (Skill* skill = dynamic_cast<Skill*>(mTabs["Stats"]->GetSlot(pos)))
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

void PlayerInterface::UpdateInventory()
{
	mTabs["Inventory"]->Update();

	if (mTabs["Inventory"]->Active() && !mTabs["Inventory"]->InUse())
	{
		mCommand = mTabs["Inventory"]->CurrentAction();

		if (mCommand == "Use")
		{
			mTabs["Inventory"]->InUse(true);
			mWaitingForUse = true;
		}
	}
	else if (mTabs["Inventory"]->Active() && mTabs["Inventory"]->InUse() && !mWaitingForUse)
		mTabs["Inventory"]->InUse(false);
}

void PlayerInterface::UpdateGear()
{
	mTabs["Gear"]->Update();

	if (mTabs["Gear"]->Active())
	{
		mCommand = mTabs["Gear"]->CurrentAction();
	}
}

void PlayerInterface::UpdatePrayer()
{
	mTabs["Prayer"]->Update();

	if (mTabs["Prayer"]->Active())
	{
		mCommand = mTabs["Prayer"]->CurrentAction();
	}
}

void PlayerInterface::UpdateMagic()
{
	mTabs["Magic"]->Update();

	if (mTabs["Magic"]->Active() && !mTabs["Magic"]->InUse())
	{
		mCommand = mTabs["Magic"]->CurrentAction();

		if (mCommand == "Cast")
		{
			mTabs["Magic"]->InUse(true);
			mWaitingForCast = true;
		}
	}
	else if (mTabs["Magic"]->Active() && mTabs["Magic"]->InUse() && !mWaitingForCast)
		mTabs["Magic"]->InUse(false);
}

void PlayerInterface::UpdateStats()
{
	mTabs["Stats"]->Update();

	if (mTabs["Stats"]->Active())
	{
		mCommand = mTabs["Stats"]->CurrentAction();
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
		else if (mTabs["Inventory"]->ContainsClick())
		{
			mPlayer.Target(mTabs["Inventory"]->GetSlot(Square::InputHandler::Instance().MousePos(), false));
		}

		mWaitingForUse = false;
	}
	else if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::right))
	{
		if (mActionsMenu == nullptr)
		{
			std::string activeItem = mPlayer.Inventory().GetItem(mPlayer.Inventory().ActiveSlot())->Name();
			std::string targetObject = "";

			if (mTabs["Inventory"]->ContainsClick())
			{
				if (Item* item = dynamic_cast<Item*>(mTabs["Inventory"]->GetSlot(Square::InputHandler::Instance().MousePos(), false)))
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

		mWaitingForCast = false;
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
		if (!mWaitingForCast && !mWaitingForUse)
		{
			mCommand = "Move";
		}
	}
}

void PlayerInterface::Update()
{
	if (mWaitingForUse)
	{
		HandleUse();
	}
	else if (mWaitingForCast)
	{
		HandleCast();
	}
	else if (!mCommand.empty())
	{
		mCommandManager.Invoke(mCommand);
		mCommand.clear();
	}

	HandleButtons();
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

	UpdateInventory();
	UpdateGear();
	UpdatePrayer();
	UpdateMagic();
	UpdateStats();

	if (!ContainsClick() && mCommand.empty())
		HandleMove();
}

void PlayerInterface::Render()
{
	for (auto& button : mButtons)
			button.second->Render();

	for (auto& tab : mTabs)
	{
		if (tab.second->Active())
			tab.second->Render();
	}

	if (mHoverSprite) mHoverSprite->Render(true);

	if (mActionsMenu) mActionsMenu->Render();
}
