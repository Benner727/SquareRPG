#include "PlayerInterface.h"

PlayerInterface::PlayerInterface(Player& player)
	: mPlayer(player), mCommandManager(&mPlayer),
	mInventory(player.Inventory()), mGear(player.Gear())
{
	mWaitingForUse = false;

	mActiveMenu = Menu::inventory;

	mGearButton = new Square::Sprite("Graphics/buttonSquare_brown.png");
	mGearButton->Parent(this);
	mGearButton->Pos(Square::Vector2(Square::Graphics::SCREEN_WIDTH - mGearButton->ScaledDimensions().x * 0.5f, Square::Graphics::SCREEN_HEIGHT - mGearButton->ScaledDimensions().y * 0.5f));

	mInventoryButton = new Square::Sprite("Graphics/buttonSquare_brown.png");
	mInventoryButton->Parent(this);
	mInventoryButton->Pos(mGearButton->Pos() - Square::VEC2_RIGHT * mInventoryButton->ScaledDimensions().x);

	mInventory.Parent(this);
	mInventory.Pos(Square::Vector2(Square::Graphics::SCREEN_WIDTH - 208, Square::Graphics::SCREEN_HEIGHT - 256 - mInventoryButton->ScaledDimensions().y));

	mGear.Parent(this);
	mGear.Pos(Square::Vector2(Square::Graphics::SCREEN_WIDTH - 208, Square::Graphics::SCREEN_HEIGHT - 256 - mGearButton->ScaledDimensions().y));
	mGear.Active(false);

	mHoverText = "";
	mHoverSprite = nullptr;
}

PlayerInterface::~PlayerInterface()
{
	delete mGearButton;
	delete mInventoryButton;

	delete mHoverSprite;
}

void PlayerInterface::HandleButtons()
{
	if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::left))
	{
		Square::Vector2 pos = Square::InputHandler::Instance().MousePos();

		if (pos.x > mInventoryButton->Pos().x - mInventoryButton->ScaledDimensions().x * 0.5f &&
			pos.x < mInventoryButton->Pos().x + mInventoryButton->ScaledDimensions().x * 0.5f &&
			pos.y > mInventoryButton->Pos().y - mInventoryButton->ScaledDimensions().y * 0.5f &&
			pos.y < mInventoryButton->Pos().y + mInventoryButton->ScaledDimensions().y * 0.5f)
		{
			if (mActiveMenu != Menu::inventory)
			{
				mActiveMenu = Menu::inventory;
				mInventory.Active(true);

				mGear.Active(false);
			}
			else
			{
				mActiveMenu = Menu::none;
				mInventory.Active(false);
			}
		}
		else if (pos.x > mGearButton->Pos().x - mGearButton->ScaledDimensions().x * 0.5f &&
			pos.x < mGearButton->Pos().x + mGearButton->ScaledDimensions().x * 0.5f &&
			pos.y > mGearButton->Pos().y - mGearButton->ScaledDimensions().y * 0.5f &&
			pos.y < mGearButton->Pos().y + mGearButton->ScaledDimensions().y * 0.5f)
		{
			if (mActiveMenu != Menu::gear)
			{
				mActiveMenu = Menu::gear;
				mGear.Active(true);

				mInventory.Active(false);
			}
			else
			{
				mActiveMenu = Menu::none;
				mGear.Active(false);
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
		if (!mInventory.MenuOpened())
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
		if (!mGear.MenuOpened())
		{
			if (Item* item = mGear.GetSlot(pos))
				hoverText += "Unequip " + item->Name();
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

void PlayerInterface::Update()
{
	if (mWaitingForUse)
	{
		if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::left))
		{
			if (mInventory.ContainsClick())
			{
				mPlayer.Target(mInventory.GetSlot(Square::InputHandler::Instance().MousePos()));
			}

			mWaitingForUse = false;
		}
	}
	else if (!mCommand.empty())
	{
		mCommandManager.Invoke(mCommand);
		mCommand.clear();
	}

	HandleButtons();
	SetHoverText();

	UpdateInventory();
	UpdateGear();
}

void PlayerInterface::Render()
{
	mInventoryButton->Render();
	mGearButton->Render();

	switch (mActiveMenu)
	{
	case Menu::inventory:
		mInventory.Render();
		break;
	case Menu::gear:
		mGear.Render();
		break;
	}

	if (mHoverSprite) mHoverSprite->Render();
}
