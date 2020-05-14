#include "MenuTabsInterface.h"

MenuTabsInterface::MenuTabsInterface(std::shared_ptr<Player> player)
	: mPlayer(player)
{
	mCommand = "";
	mWaitingForInteraction = false;

	AddButton("Magic");
	AddButton("Prayer");
	AddButton("Gear");
	AddButton("Inventory");
	AddButton("Stats");
	AddButton("Combat");

	mTabs["Inventory"] = new InventoryInterface(mPlayer->Inventory());
	mTabs["Inventory"]->Parent(this);
	mTabs["Inventory"]->Pos(Square::Vector2(Square::Graphics::SCREEN_WIDTH - 208, Square::Graphics::SCREEN_HEIGHT - 256 - mButtons["Inventory"]->Height()));

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

	mTabs["Stats"] = new StatsInterface(mPlayer->Skills());
	mTabs["Stats"]->Parent(this);
	mTabs["Stats"]->Pos(Square::Vector2(Square::Graphics::SCREEN_WIDTH - 208, Square::Graphics::SCREEN_HEIGHT - 256 - mButtons["Stats"]->Height()));
	mTabs["Stats"]->Active(false);
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
	mButtons[button] = new Button("Graphics/buttonSquare_brown.png");
	mButtons[button]->Parent(this);
	mButtons[button]->Pos(Square::Vector2(Square::Graphics::SCREEN_WIDTH - mButtons[button]->Width() * 0.5f - (mButtons[button]->Width() * (mButtons.size() - 1)),
		Square::Graphics::SCREEN_HEIGHT - mButtons[button]->Height() * 0.5f));
}

void MenuTabsInterface::HandleButtons()
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
