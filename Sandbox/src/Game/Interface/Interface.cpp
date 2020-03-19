#include "Interface.h"

Interface::Interface(Player& player) :
	mPlayer(player), mMenu(), mInventory(player.Inventory()), mActiveMenu(-1),
	mInputHandler(Square::InputHandler::Instance())
{
	mMenu.Parent(this);
	mInventory.Parent(this);
}

Interface::~Interface()
{
}

void Interface::HandleInput()
{

	if (mMenu.Pressed())
	{
		mMenu.LeftClick(mInputHandler.MousePos());
		mActiveMenu = mMenu.ActiveSlot();
		if (mMenu.ActiveSlot() == -1) mPlayer.Inventory().ActiveSlot(-1);
	}
	mInventory.Update();
}

void Interface::Render()
{
	mMenu.Render();

	if (mActiveMenu >= 0)
	{
		mInventory.Render();
	}
}
