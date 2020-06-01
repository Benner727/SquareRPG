#include "MenuTabsInterface.h"

MenuTabsInterface::MenuTabsInterface(std::shared_ptr<Player> player)
	: mPlayer(player)
{
	mCommand = "";
	mWaitingForInteraction = false;
	mSelectingSpell = false;

	AddButton("Magic");
	AddButton("Prayer");
	AddButton("Gear");
	AddButton("Inventory");
	AddButton("Stats");
	AddButton("Combat");

	Init();
}

MenuTabsInterface::~MenuTabsInterface()
{
	for (auto button : mButtons)
		delete button.second;

	for (auto tab : mTabs)
		delete tab.second;
}

void MenuTabsInterface::AddButton(std::string button)
{
	mButtons[button] = new Button("Interface/buttonSquare_brown.png");
	mButtons[button]->Parent(this);
	mButtons[button]->Pos(Square::Vector2(Square::Graphics::SCREEN_WIDTH - mButtons[button]->Width() * 0.5f - (mButtons[button]->Width() * (mButtons.size() - 1)),
		Square::Graphics::SCREEN_HEIGHT - mButtons[button]->Height() * 0.5f));
}

void MenuTabsInterface::Init()
{
	mTabs["Combat"] = new CombatInterface(*mPlayer);
	mTabs["Combat"]->Parent(this);
	mTabs["Combat"]->Pos(Square::Vector2(Square::Graphics::SCREEN_WIDTH - 208, Square::Graphics::SCREEN_HEIGHT - 256 - mButtons["Combat"]->Height()));
	mTabs["Combat"]->Active(false);

	mTabs["Stats"] = new StatsInterface(mPlayer->Skills());
	mTabs["Stats"]->Parent(this);
	mTabs["Stats"]->Pos(Square::Vector2(Square::Graphics::SCREEN_WIDTH - 208, Square::Graphics::SCREEN_HEIGHT - 256 - mButtons["Stats"]->Height()));
	mTabs["Stats"]->Active(false);

	mTabs["Inventory"] = new InventoryInterface(mPlayer->Inventory());
	mTabs["Inventory"]->Parent(this);
	mTabs["Inventory"]->Pos(Square::Vector2(Square::Graphics::SCREEN_WIDTH - 208, Square::Graphics::SCREEN_HEIGHT - 256 - mButtons["Inventory"]->Height()));
	//mTabs["Inventory"]->Active(false);

	mTabs["Gear"] = new GearInterface(mPlayer->Gear());
	mTabs["Gear"]->Parent(this);
	mTabs["Gear"]->Pos(Square::Vector2(Square::Graphics::SCREEN_WIDTH - 208, Square::Graphics::SCREEN_HEIGHT - 256 - mButtons["Gear"]->Height()));
	mTabs["Gear"]->Active(false);

	mTabs["Prayer"] = new PrayerInterface(mPlayer->PrayerBook());
	mTabs["Prayer"]->Parent(this);
	mTabs["Prayer"]->Pos(Square::Vector2(Square::Graphics::SCREEN_WIDTH - 208, Square::Graphics::SCREEN_HEIGHT - 256 - mButtons["Prayer"]->Height()));
	mTabs["Prayer"]->Active(false);

	mTabs["Magic"] = new MagicInterface(mPlayer->SpellBook());
	mTabs["Magic"]->Parent(this);
	mTabs["Magic"]->Pos(Square::Vector2(Square::Graphics::SCREEN_WIDTH - 208, Square::Graphics::SCREEN_HEIGHT - 256 - mButtons["Magic"]->Height()));
	mTabs["Magic"]->Active(false);

	mTabs["Spell"] = new SpellInterface(mPlayer->SpellBook());
	mTabs["Spell"]->Parent(this);
	mTabs["Spell"]->Pos(Square::Vector2(Square::Graphics::SCREEN_WIDTH - 208, Square::Graphics::SCREEN_HEIGHT - 256 - mButtons["Magic"]->Height()));
	mTabs["Spell"]->Active(false);
}

void MenuTabsInterface::HandleButtons()
{
	if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::left))
	{
		bool menuOpened = false;
		for (const auto& tab : mTabs)
		{
			if (tab.second->Active())
			{
				if (tab.second->MenuOpened())
					menuOpened = true;
			}
		}

		if (!menuOpened)
		{
			for (auto& button : mButtons)
			{
				if (button.second->Pressed())
					SwitchTab(button.first);
			}
		}
	}
}

void MenuTabsInterface::SwitchTab(std::string key)
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
			tab.second->InUse(false);
			mWaitingForInteraction = false;
			mSelectingSpell = false;
		}
	}
}

void MenuTabsInterface::UpdateInventory()
{
	mTabs["Inventory"]->Update();

	if (mTabs["Inventory"]->Active() && !mTabs["Inventory"]->InUse())
	{
		mCommand = mTabs["Inventory"]->CurrentAction();

		if (mCommand == "Use")
		{
			mTabs["Inventory"]->InUse(true);
			mWaitingForInteraction = true;
		}
	}
	else if (mTabs["Inventory"]->Active() && mTabs["Inventory"]->InUse() && !mWaitingForInteraction)
		mTabs["Inventory"]->InUse(false);
}

void MenuTabsInterface::UpdateGear()
{
	mTabs["Gear"]->Update();

	if (mTabs["Gear"]->Active())
	{
		mCommand = mTabs["Gear"]->CurrentAction();
	}
}

void MenuTabsInterface::UpdatePrayer()
{
	mTabs["Prayer"]->Update();

	if (mTabs["Prayer"]->Active())
	{
		mCommand = mTabs["Prayer"]->CurrentAction();
	}
}

void MenuTabsInterface::UpdateMagic()
{
	mTabs["Magic"]->Update();

	if (mTabs["Magic"]->Active() && !mTabs["Magic"]->InUse())
	{
		mCommand = mTabs["Magic"]->CurrentAction();

		if (mCommand == "Cast")
		{
			mTabs["Magic"]->InUse(true);
			mWaitingForInteraction = true;
		}
	}
	else if (mTabs["Magic"]->Active() && mTabs["Magic"]->InUse() && !mWaitingForInteraction)
		mTabs["Magic"]->InUse(false);
}

void MenuTabsInterface::UpdateStats()
{
	mTabs["Stats"]->Update();

	if (mTabs["Stats"]->Active())
	{
		mCommand = mTabs["Stats"]->CurrentAction();
	}
}

void MenuTabsInterface::UpdateCombat()
{
	mTabs["Combat"]->Update();

	if (mTabs["Combat"]->Active() && !mTabs["Combat"]->InUse())
	{
		mCommand = mTabs["Combat"]->CurrentAction();

		if (mCommand == "Autocast")
		{
			mTabs["Combat"]->Active(false);
			mTabs["Spell"]->Active(true);
			mTabs["Combat"]->InUse(true);
			mSelectingSpell = true;
		}
	}
	else if (mTabs["Combat"]->InUse() && !mSelectingSpell)
	{
		mTabs["Combat"]->Active(true);
		mTabs["Spell"]->Active(false);
		mTabs["Combat"]->InUse(false);
	}
}

void MenuTabsInterface::UpdateSpell()
{
	mTabs["Spell"]->Update();

	if (mTabs["Spell"]->Active())
	{
		mCommand = mTabs["Spell"]->CurrentAction();

		if (mCommand == "Select Spell")
			mSelectingSpell = false;
	}
}

bool MenuTabsInterface::ContainsClick() const
{
	for (const auto& button : mButtons)
	{
		if (button.second->Pressed())
			return true;
	}

	for (const auto& tab : mTabs)
	{
		if (tab.second->Active())
		{
			if (tab.second->ContainsClick())
				return true;
		}
	}

	return false;
}

void MenuTabsInterface::Update()
{
	HandleButtons();

	UpdateInventory();
	UpdateGear();
	UpdatePrayer();
	UpdateMagic();
	UpdateStats();
	UpdateCombat();
	UpdateSpell();
}

void MenuTabsInterface::Render()
{
	for (auto& button : mButtons)
		button.second->Render();

	for (auto& tab : mTabs)
	{
		if (tab.second->Active())
			tab.second->Render();
	}
}
