#include "Interface.h"

Interface::Interface(Player player) :
	mPlayer(player), mMenu(), mInputHandler(Square::InputHandler::Instance())
{
	mMenu.Parent(this);
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
}
