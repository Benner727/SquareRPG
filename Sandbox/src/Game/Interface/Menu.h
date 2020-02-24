#pragma once

#include <Square.h>

#include "IInputContainer.h"

class Menu : public IInputContainer
{
public:
	const std::string MENU_PATH = "Graphics/menu.png";
	const std::string BUTTON_UNSELECTED = "Graphics/resting-menu-button.png";
	const std::string BUTTON_SELECTED = "Graphics/selected-menu-button.png";

	static const int MENU_WIDTH = 256;
	static const int MENU_HEIGHT = 64;
	static const int BUTTON_WIDTH = 64;
	static const int BUTTON_HEIGHT = 64;

private:
	const Square::Vector2 mPosition;
	//std::vector<Square::Sprite> mInputs;
	Square::Sprite mMenu;
	Square::Sprite mButtonUnselected;
	Square::Sprite mButtonSelected;
	int mActiveSlot = -1;

	enum MenuSlot {
		skills, combat, inventory, equipment, TOTAL_SLOTS
	};

public:
	Menu();
	~Menu();

	int ActiveSlot() { return mActiveSlot; }

	bool MouseIsOver(Square::Vector2 position);
	void HandleClick(Square::Vector2 position);
	void Render();

};

