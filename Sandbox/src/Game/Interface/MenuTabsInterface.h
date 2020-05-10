#pragma once

#include <Square.h>

#include "Game/Player/Player.h"
#include "Game/Map/Map.h"
#include "Game/Interface/InventoryInterface.h"
#include "Game/Interface/GearInterface.h"
#include "Game/Interface/PrayerInterface.h"
#include "Game/Interface/MagicInterface.h"
#include "Game/Interface/StatsInterface.h"
#include "Game/Interface/Tools/Button.h"

class MenuTabsInterface : public Square::GameObject
{
private:
	Player& mPlayer;

	std::map<std::string, IMenuTab*> mTabs;
	std::map<std::string, Button*> mButtons;

	std::string mCommand;
	bool mWaitingForInteraction;

	void AddButton(std::string button);

	void HandleButtons();
	void SwitchTab(std::string key);

	void UpdateInventory();
	void UpdateGear();
	void UpdatePrayer();
	void UpdateMagic();
	void UpdateStats();

public:
	MenuTabsInterface(Player& player);
	~MenuTabsInterface();

	inline std::string Command() const { return mCommand; }
	inline bool WaitingForInteraction() const { return mWaitingForInteraction; }
	
	inline IMenuTab* Tab(std::string tab) { return mTabs[tab]; }

	inline void Reset()
	{
		mCommand.clear();
		mWaitingForInteraction = false;
	}

	bool ContainsClick() const;

	void Update();
	void Render();
};