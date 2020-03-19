#include "IInputContainer.h"

bool IInputContainer::MouseIsOver()
{
	Square::Vector2 position = mInputHandler.MousePos();
	return (
		(position.x >= mPosition.x - mWidth / 2 && position.x <= mPosition.x + mWidth / 2) &&
		(position.y >= mPosition.y - mHeight / 2 && position.y <= mPosition.y + mHeight / 2)
	);
}

bool IInputContainer::Pressed()
{
	return mInputHandler.MouseButtonPressed(Square::InputHandler::MOUSE_BUTTON::left) && MouseIsOver();
}
