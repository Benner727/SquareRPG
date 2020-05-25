#pragma once

#include <Square.h>

#include "Game/World/Player/Player.h"
#include "Game/World/Map/Map.h"
#include "Game/Interface/Tabs/InventoryInterface.h"
#include "Game/Interface/Tabs/GearInterface.h"
#include "Game/Interface/Tabs/PrayerInterface.h"
#include "Game/Interface/Tabs/MagicInterface.h"
#include "Game/Interface/Tabs/StatsInterface.h"
#include "Game/Interface/Tabs/CombatInterface.h"
#include "Game/Interface/Tools/Button.h"

class MenuTabsInterface : public Square::GameObject
{
private:
	std::shared_ptr<Player> mPlayer;

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
	void UpdateCombat();

public:
	MenuTabsInterface(std::shared_ptr<Player> player);
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