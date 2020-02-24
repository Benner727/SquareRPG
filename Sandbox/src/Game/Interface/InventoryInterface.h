#pragma once

#include <Square.h>

#include "Game/Interface/IInputContainer.h"
#include "Game/Player/Inventory.h"

class InventoryInterface : public IInputContainer
{
public:
	const std::string CONTAINER_PATH = "Graphics/opened-menu.png";
	const std::string BUTTON_UNSELECTED = "Graphics/resting-item.png";
	const std::string BUTTON_SELECTED = "Graphics/selected-item.png";

	static const int CONTAINER_WIDTH = 256;
	static const int CONTAINER_HEIGHT = 320;
	static const int BUTTON_WIDTH = 64;
	static const int BUTTON_HEIGHT = 64;

private:
	Square::Sprite mContainer;
	Square::Sprite mButtonUnselected;
	Square::Sprite mButtonSelected;
	Square::Vector2 mPosition;

	Inventory& mInventory;

public:
	InventoryInterface(Inventory& inventory);
	~InventoryInterface();

	bool MouseIsOver(Square::Vector2 position);
	void HandleClick(Square::Vector2 position);
	void Render();
};
