#include "MenuContainer.h"

MenuContainer::MenuContainer()
{
	mWidth = MENU_WIDTH;
	mHeight = MENU_HEIGHT;
	mPosition = Square::Vector2(
		Square::Graphics::SCREEN_WIDTH - MENU_WIDTH / 2,
		Square::Graphics::SCREEN_HEIGHT - MENU_HEIGHT / 2);

	mContainer = Square::Sprite(MENU_PATH, 0, 0, MENU_WIDTH, MENU_HEIGHT);
	mContainer.Pos(mPosition);

	mButtonUnselected = Square::Sprite(BUTTON_UNSELECTED, 0, 0, BUTTON_WIDTH, BUTTON_HEIGHT);
	mButtonSelected = Square::Sprite(BUTTON_SELECTED, 0, 0, BUTTON_WIDTH, BUTTON_HEIGHT);

	mButtonSelected.Parent(&mContainer);
	mButtonUnselected.Parent(&mContainer);
}

MenuContainer::~MenuContainer()
{
}

void MenuContainer::HandleClick(Square::Vector2 position)
{
	int relativeX = position.x - (Square::Graphics::SCREEN_WIDTH - MENU_WIDTH);
	int slotIndex = relativeX / BUTTON_WIDTH;
	(mActiveSlot != slotIndex) ? mActiveSlot = slotIndex : mActiveSlot = -1;
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
