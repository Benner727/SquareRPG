#pragma once

#include "Game/Commands/CommandManager.h"
#include "Game/Interface/MenuTabsInterface.h"
#include "Game/Map/Map.h"

class PlayerInterface : public Square::GameObject
{
private:
	Player& mPlayer;
	Map& mMap;

	MenuTabsInterface* mMenuTabsInterface;

	CommandManager mCommandManager;
	std::string mCommand;

	bool mWaitingForInteraction;

	std::string mHoverText;
	Square::Text* mHoverSprite;

	ActionsMenu* mActionsMenu;
	Square::GameObject* mTargetObject;

	void SetHoverText();

	void HandleUse();
	void HandleCast();

	void HandleMove();

public:
	PlayerInterface(Player& player, Map& map);
	~PlayerInterface();

	void Update();
	void Render();
};