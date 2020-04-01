#pragma once

#include "Game/Commands/CommandManager.h"
#include "Game/Interface/InventoryInterface.h"
#include "Game/Interface/GearInterface.h"

class PlayerInterface : public Square::GameObject
{
private:
	enum class Menu { none, inventory, gear };

	Player& mPlayer;
	CommandManager mCommandManager;

	InventoryInterface mInventory;
	GearInterface mGear;

	std::string mCommand;
	bool mWaitingForUse;

	std::string mHoverText;
	Square::Text* mHoverSprite;

	ActionsMenu* mActionsMenu;
	Square::GameObject* mTargetObject;

	Menu mActiveMenu;

	Square::Sprite* mInventoryButton;
	Square::Sprite* mGearButton;

	void HandleButtons();
	void SetHoverText();

	void UpdateInventory();
	void UpdateGear();

public:
	PlayerInterface(Player& player);
	~PlayerInterface();

	void Update();
	void Render();
};