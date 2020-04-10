#pragma once

#include "Game/Commands/CommandManager.h"
#include "Game/Interface/InventoryInterface.h"
#include "Game/Interface/GearInterface.h"
#include "Game/Interface/PrayerInterface.h"

class PlayerInterface : public Square::GameObject
{
private:
	enum class Menu { none, inventory, gear, prayer };

	Player& mPlayer;
	CommandManager mCommandManager;

	InventoryInterface mInventory;
	GearInterface mGear;
	PrayerInterface mPrayer;

	std::string mCommand;
	bool mWaitingForUse;

	std::string mHoverText;
	Square::Text* mHoverSprite;

	ActionsMenu* mActionsMenu;
	Square::GameObject* mTargetObject;

	Menu mActiveMenu;

	std::map<std::string, Square::Sprite*> mButtons;

	void AddButton(std::string button);

	void HandleButtons();
	void SetHoverText();

	void UpdateInventory();
	void UpdateGear();
	void UpdatePrayer();

public:
	PlayerInterface(Player& player);
	~PlayerInterface();

	void Update();
	void Render();
};