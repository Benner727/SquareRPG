#pragma once

#include <Square.h>

#include "Game/Interface/IInputContainer.h"
#include "Game/Player/Inventory.h"

class InventoryContainer : public IInputContainer
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
	Inventory& mInventory;
	Square::InputHandler& mInputHandler;

public:
	InventoryContainer(Inventory& inventory);
	~InventoryContainer();

	int SlotIndex(Square::Vector2 position);
	void LeftClick(Square::Vector2 position);
	void RightClick(Square::Vector2 position);
	void Drag(Square::Vector2 position);
	void Hover(Square::Vector2 position);

	void Update();
	void Render();
};
