#pragma once

#include <Square.h>

#include "Game/Player/Player.h"
#include "MenuContainer.h"
#include "InventoryContainer.h"
#include "Tooltip.h"

class Interface : public Square::GameObject
{
private:
	Player& mPlayer;
	MenuContainer mMenu;
	InventoryContainer mInventory;

	int mActiveMenu;

	Square::InputHandler& mInputHandler;

public:
	Interface(Player& player);
	~Interface();

	void HandleInput();
	void Render();
};

