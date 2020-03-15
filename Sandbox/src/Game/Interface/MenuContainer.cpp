#include "MenuContainer.h"

MenuContainer::MenuContainer()
{
	mWidth = MENU_WIDTH;
	mHeight = MENU_HEIGHT;
	mPosition = Square::Vector2(
		Square::Graphics::SCREEN_WIDTH - MENU_WIDTH / 2,
		Square::Graphics::SCREEN_HEIGHT - MENU_HEIGHT / 2) - PADDING;

	mContainer = Square::Sprite(MENU_PATH);
	mContainer.Pos(mPosition);

	mButtonUnselected = Square::Sprite(BUTTON_UNSELECTED);
	mButtonSelected = Square::Sprite(BUTTON_SELECTED);
	mButtonSelected.Parent(&mContainer);
	mButtonUnselected.Parent(&mContainer);
}

MenuContainer::~MenuContainer()
{
}

int MenuContainer::SlotIndex(Square::Vector2 position)
{
	return -1;
}

void MenuContainer::LeftClick(Square::Vector2 position)
{
	int relativeX = position.x - (Square::Graphics::SCREEN_WIDTH - MENU_WIDTH);
	int slotIndex = relativeX / BUTTON_WIDTH;
	(mActiveSlot != slotIndex) ? mActiveSlot = slotIndex : mActiveSlot = -1;
}

void MenuContainer::RightClick(Square::Vector2 position)
{
}

void MenuContainer::Drag(Square::Vector2 position)
{
}

void MenuContainer::Hover(Square::Vector2 position)
{
}

void MenuContainer::Update()
{
	Square::Vector2 position = mInputHandler.MousePos();

	if (MouseIsOver(position))
	{
		Hover(position);
		LeftClick(position);
		Drag(position);
	}
	else
	{
		mDragPosition = Square::Vector2(-1, -1);
		mActiveSlot = -1;
	}

}

void MenuContainer::Render()
{
	mContainer.Render();

	for (int slot = 0; slot < MenuSlot::TOTAL_SLOTS; slot++)
	{
		Square::Vector2 buttonPosition = Square::Vector2(-MENU_WIDTH/2 + BUTTON_WIDTH/2 + (slot*BUTTON_WIDTH), 0);
		if (mActiveSlot == slot)
		{
			mButtonSelected.Pos(buttonPosition);
			mButtonSelected.Render();
		}
		else
		{
			mButtonUnselected.Pos(buttonPosition);
			mButtonUnselected.Render();
		}
	}
}
