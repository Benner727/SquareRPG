#pragma once

#include <Square.h>

#include "IInputContainer.h"

class MenuContainer : public IInputContainer
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
	enum MenuSlot {
		skills, combat, inventory, equipment, TOTAL_SLOTS
	};


public:
	MenuContainer();
	~MenuContainer();

	void LeftClick(Square::Vector2 position);
	void RightClick(Square::Vector2 position);
	void Drag(Square::Vector2 position);
	void Hover(Square::Vector2 position);

	int ActiveSlot() { return mActiveSlot; }

	void Update();
	void Render();

};
