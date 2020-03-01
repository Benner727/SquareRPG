#include "Interface.h"

Interface::Interface(Player& player) :
	mPlayer(player), mMenu(), mInventory(player.Inventory()),
	mInputHandler(Square::InputHandler::Instance()),
	mTooltip("hello")
{
	mMenu.Parent(this);
	mInventory.Parent(this);
	mTooltip.Text().Parent(this);
	InitializeBackground();
}

Interface::~Interface()
{
}

void Interface::InitializeBackground()
{
	mTooltip.Pos(Square::Vector2(100, 100));
}

void Interface::HandleInput()
{

	if (mInputHandler.MouseButtonPressed(Square::InputHandler::MOUSE_BUTTON::left))
	{
		if (mMenu.MouseIsOver(mInputHandler.MousePos()))
		{
			mMenu.LeftClick(mInputHandler.MousePos());
			mActiveMenu = mMenu.ActiveSlot();
			if (mMenu.ActiveSlot() == -1) mPlayer.Inventory().ActiveSlot(-1);
		}
	}
	mInventory.Update();
}

void Interface::Render()
{
	mMenu.Render();
	//mTooltip.Text().Render();

	if (mActiveMenu >= 0)
	{
		mInventory.Render();
	}
}
