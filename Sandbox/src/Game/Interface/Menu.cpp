#include "Menu.h"

Menu::Menu() :
	mPosition(Square::Vector2(
		Square::Graphics::SCREEN_WIDTH - MENU_WIDTH / 2,
		Square::Graphics::SCREEN_HEIGHT - MENU_HEIGHT / 2)
	),
	mMenu(Square::Sprite(MENU_PATH, 0, 0, MENU_WIDTH, MENU_HEIGHT)),
	mButtonUnselected(Square::Sprite(BUTTON_UNSELECTED, 0, 0, BUTTON_WIDTH, BUTTON_HEIGHT)),
	mButtonSelected(Square::Sprite(BUTTON_SELECTED, 0, 0, BUTTON_WIDTH, BUTTON_HEIGHT))
{
	mMenu.Pos(mPosition);

	mButtonSelected.Parent(&mMenu);
	mButtonUnselected.Parent(&mMenu);
}

Menu::~Menu()
{
}

bool Menu::MouseIsOver(Square::Vector2 position)
{ // how to use IsBetween?
	return (
		(position.x >= mPosition.x - MENU_WIDTH/2  && position.x <= mPosition.x + MENU_WIDTH/2) &&
		(position.y >= mPosition.y - MENU_HEIGHT/2 && position.y <= mPosition.y + MENU_HEIGHT/2)
	);
}

void Menu::HandleClick(Square::Vector2 position)
{
	int relativeX = position.x - (Square::Graphics::SCREEN_WIDTH - MENU_WIDTH);
	int slotIndex = relativeX / BUTTON_WIDTH;
	if (mActiveSlot != slotIndex) mActiveSlot = slotIndex;
	else mActiveSlot = -1;
}

void Menu::Render()
{
	mMenu.Render();

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
