#pragma once

#include <Square.h>

#include "Game/Commands/ICommand.h";

class IInputContainer : public Square::GameObject
{

protected:
	int mWidth;
	int mHeight;

	Square::Vector2 mPosition;
	Square::Sprite mContainer;
	Square::Sprite mButtonUnselected;
	Square::Sprite mButtonSelected;
	Square::InputHandler& mInputHandler = Square::InputHandler::Instance();

	int mActiveSlot = -1;
	Square::Vector2 mDragPosition = Square::Vector2(-1, -1);
	//std::vector<ICommand> mCommands;

public:
	virtual int SlotIndex(Square::Vector2 position) = 0;
	virtual void LeftClick(Square::Vector2 position) = 0;
	virtual void RightClick(Square::Vector2 position) = 0;
	virtual void Drag(Square::Vector2 position) = 0;
	virtual void Hover(Square::Vector2 position) = 0;
	bool MouseIsOver(Square::Vector2 position);
	bool CanDrag(Square::Vector2 position);

	//std::vector<ICommand> Commands() { return mCommands; }

	virtual void Update() = 0;
	virtual void Render() = 0;
	// container

};
