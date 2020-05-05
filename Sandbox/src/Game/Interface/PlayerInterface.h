#pragma once

#include "Game/Commands/CommandManager.h"
#include "Game/Interface/InventoryInterface.h"
#include "Game/Interface/GearInterface.h"
#include "Game/Interface/PrayerInterface.h"
#include "Game/Interface/MagicInterface.h"
#include "Game/Interface/StatsInterface.h"
#include "Game/Interface/Button.h"

#include "Game/Map/Map.h"

class PlayerInterface : public Square::GameObject
{
private:
	Player& mPlayer;
	Map& mMap;
	CommandManager mCommandManager;

	std::map<std::string, IMenuTab*> mTabs;
	std::map<std::string, Button*> mButtons;

	std::string mCommand;
	bool mWaitingForUse;
	bool mWaitingForCast;

	std::string mHoverText;
	Square::Text* mHoverSprite;

	ActionsMenu* mActionsMenu;
	Square::GameObject* mTargetObject;

	void AddButton(std::string button);

	bool ContainsClick() const;

	void HandleButtons();
	void SwitchTab(std::string key);

	void SetHoverText();

	void UpdateInventory();
	void UpdateGear();
	void UpdatePrayer();
	void UpdateMagic();
	void UpdateStats();

	void HandleUse();
	void HandleCast();

	void HandleMove();

public:
	PlayerInterface(Player& player, Map& map);
	~PlayerInterface();

	void Update();
	void Render();
};