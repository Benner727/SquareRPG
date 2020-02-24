#include "Interface.h"

Interface::Interface(Player player) :
	mPlayer(player), mMenu(), mInventory(player.Inventory()),
	mInputHandler(Square::InputHandler::Instance())
{
	mMenu.Parent(this);
	mInventory.Parent(this);
	InitializeBackground();
}

Interface::~Interface()
{
}

void Interface::InitializeBackground()
{
}

void Interface::HandleInput()
{
	if (mInputHandler.MouseButtonPressed(Square::InputHandler::MOUSE_BUTTON::left))
	{
		if (mMenu.MouseIsOver(mInputHandler.MousePos()))
		{
			mMenu.HandleClick(mInputHandler.MousePos());
			mActiveMenu = mMenu.ActiveSlot();
		}

		if (mInventory.MouseIsOver(mInputHandler.MousePos()))
		{
			mInventory.HandleClick(mInputHandler.MousePos());
		}
	}
}

void Interface::Render()
{
	//for (Square::Sprite sprite : mBackgroundSprites)
	//{
	//	sprite.Render();
	//}

	mMenu.Render();

	if (mActiveMenu >= 0)
	{
		mInventory.Render();
	}
}
