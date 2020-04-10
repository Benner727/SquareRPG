#include "PlayerInterface.h"

PlayerInterface::PlayerInterface(Player& player)
	: mPlayer(player), mCommandManager(&mPlayer),
	mInventory(player.Inventory()), mGear(player.Gear()),
	mPrayer(player.PrayerBook())
{
	mWaitingForUse = false;

	mActiveMenu = Menu::inventory;

	AddButton("SpellBook");
	AddButton("Prayer");
	AddButton("Gear");
	AddButton("Inventory");
	AddButton("Stats");
	AddButton("Combat");

	mInventory.Parent(this);
	mInventory.Pos(Square::Vector2(Square::Graphics::SCREEN_WIDTH - 208, Square::Graphics::SCREEN_HEIGHT - 256 - mButtons["Inventory"]->ScaledDimensions().y));

	mGear.Parent(this);
	mGear.Pos(Square::Vector2(Square::Graphics::SCREEN_WIDTH - 208, Square::Graphics::SCREEN_HEIGHT - 256 - mButtons["Gear"]->ScaledDimensions().y));
	mGear.Active(false);

	mPrayer.Parent(this);
	mPrayer.Pos(Square::Vector2(Square::Graphics::SCREEN_WIDTH - 208, Square::Graphics::SCREEN_HEIGHT - 256 - mButtons["Prayer"]->ScaledDimensions().y));
	mPrayer.Active(false);

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
	mButtons[button] = new Square::Sprite("Graphics/buttonSquare_brown.png");
	mButtons[button]->Parent(this);
	mButtons[button]->Pos(Square::Vector2(Square::Graphics::SCREEN_WIDTH - mButtons[button]->ScaledDimensions().x * 0.5f - (mButtons[button]->ScaledDimensions().x * (mButtons.size() - 1)), Square::Graphics::SCREEN_HEIGHT - mButtons[button]->ScaledDimensions().y * 0.5f));
}

void PlayerInterface::HandleButtons()
{
	if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::left))
	{
		Square::Vector2 pos = Square::InputHandler::Instance().MousePos();

		if (pos.x > mButtons["Inventory"]->Pos().x - mButtons["Inventory"]->ScaledDimensions().x * 0.5f &&
			pos.x < mButtons["Inventory"]->Pos().x + mButtons["Inventory"]->ScaledDimensions().x * 0.5f &&
			pos.y > mButtons["Inventory"]->Pos().y - mButtons["Inventory"]->ScaledDimensions().y * 0.5f &&
			pos.y < mButtons["Inventory"]->Pos().y + mButtons["Inventory"]->ScaledDimensions().y * 0.5f)
		{
			if (mActiveMenu != Menu::inventory)
			{
				mActiveMenu = Menu::inventory;
				mInventory.Active(true);

				mGear.Active(false);
				mPrayer.Active(false);
			}
			else
			{
				mActiveMenu = Menu::none;
				mInventory.Active(false);
			}
		}
		else if (pos.x > mButtons["Gear"]->Pos().x - mButtons["Gear"]->ScaledDimensions().x * 0.5f &&
			pos.x < mButtons["Gear"]->Pos().x + mButtons["Gear"]->ScaledDimensions().x * 0.5f &&
			pos.y > mButtons["Gear"]->Pos().y - mButtons["Gear"]->ScaledDimensions().y * 0.5f &&
			pos.y < mButtons["Gear"]->Pos().y + mButtons["Gear"]->ScaledDimensions().y * 0.5f)
		{
			if (mActiveMenu != Menu::gear)
			{
				mActiveMenu = Menu::gear;
				mGear.Active(true);

				mInventory.Active(false);
				mPrayer.Active(false);
			}
			else
			{
				mActiveMenu = Menu::none;
				mGear.Active(false);
			}
		}
		else if (pos.x > mButtons["Prayer"]->Pos().x - mButtons["Prayer"]->ScaledDimensions().x * 0.5f &&
			pos.x < mButtons["Prayer"]->Pos().x + mButtons["Prayer"]->ScaledDimensions().x * 0.5f &&
			pos.y > mButtons["Prayer"]->Pos().y - mButtons["Prayer"]->ScaledDimensions().y * 0.5f &&
			pos.y < mButtons["Prayer"]->Pos().y + mButtons["Prayer"]->ScaledDimensions().y * 0.5f)
		{
			if (mActiveMenu != Menu::prayer)
			{
				mActiveMenu = Menu::prayer;
				mPrayer.Active(true);

				mInventory.Active(false);
				mGear.Active(false);
			}
			else
			{
				mActiveMenu = Menu::none;
				mPrayer.Active(false);
			}
		}
	}
}

void PlayerInterface::SetHoverText()
{
	Square::Vector2 pos = Square::InputHandler::Instance().MousePos();

	std::string hoverText = "";

	switch (mActiveMenu)
	{
	case Menu::inventory:
		if (!mInventory.MenuOpened() && mActionsMenu == nullptr)
		{
			if (mWaitingForUse)
			{
				hoverText += "Use " + mPlayer.Inventory().GetItem(mPlayer.Inventory().ActiveSlot())->Name() + " -> ";
			}

			if (Item* item = mInventory.GetSlot(pos))
			{
				if (mWaitingForUse)
				{
					hoverText += item->Name();
				}
				else
					hoverText += item->InventoryActions().front() + " " + item->Name();
			}
		}
		break;
	case Menu::gear:
		if (!mGear.MenuOpened() && mActionsMenu == nullptr)
		{
			if (Item* item = mGear.GetSlot(pos))
				hoverText += "Unequip " + item->Name();
		}
		break;
	case Menu::prayer:
		if (!mPrayer.MenuOpened() && mActionsMenu == nullptr)
		{
			if (Aura* aura = mPrayer.GetSlot(pos))
				hoverText += (aura->Activated() ? "Deactivate " : "Activate ") + aura->Name();
		}
		break;
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
	mInventory.Update();

	if (mInventory.Active())
	{
		mCommand = mInventory.CurrentAction();

		if (mCommand == "Use")
		{
			mInventory.Active(false);
			mWaitingForUse = true;
		}
	}
	else if (mActiveMenu == Menu::inventory && !mWaitingForUse)
		mInventory.Active(true);
}

void PlayerInterface::UpdateGear()
{
	mGear.Update();

	if (mGear.Active())
	{
		mCommand = mGear.CurrentAction();
	}
}

void PlayerInterface::UpdatePrayer()
{
	mPrayer.Update();

	if (mPrayer.Active())
	{
		mCommand = mPrayer.CurrentAction();
	}
}

void PlayerInterface::Update()
{
	if (mWaitingForUse)
	{
		if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::left))
		{
			if (mActionsMenu)
			{
				mActionsMenu->Active(false);		
				if (!mActionsMenu->Action().empty())
					mPlayer.Target(mTargetObject);
			}
			else if (mInventory.ContainsClick())
			{
				mPlayer.Target(mInventory.GetSlot(Square::InputHandler::Instance().MousePos()));
			}

			mWaitingForUse = false;
		}
		else if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::right))
		{
			if (mActionsMenu == nullptr)
			{
				std::string activeItem = mPlayer.Inventory().GetItem(mPlayer.Inventory().ActiveSlot())->Name();
				std::string targetObject = "";

				if (mInventory.ContainsClick())
				{
					if (Item* item = mInventory.GetSlot(Square::InputHandler::Instance().MousePos()))
					{
						targetObject = item->Name();
						mTargetObject = item;
					}
				}

				mActionsMenu = new ActionsMenu("Options", { mHoverText }, Square::InputHandler::Instance().MousePos());
			}
		}
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
}

void PlayerInterface::Render()
{
	for (auto button : mButtons)
			button.second->Render();

	switch (mActiveMenu)
	{
	case Menu::inventory:
		mInventory.Render();
		break;
	case Menu::gear:
		mGear.Render();
		break;
	case Menu::prayer:
		mPrayer.Render();
		break;
	}

	if (mHoverSprite) mHoverSprite->Render();

	if (mActionsMenu) mActionsMenu->Render();
}
