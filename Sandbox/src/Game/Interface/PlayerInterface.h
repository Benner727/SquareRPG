#pragma once

#include "Game/Commands/CommandManager.h"
#include "Game/Interface/MenuTabsInterface.h"
#include "Game/GameGrid.h"
#include "Game/Interface/MessageLog.h"

class PlayerInterface : public Square::GameObject
{
private:
	Player& mPlayer;
	Map& mMap;

	GameGrid mGameGrid;

	MenuTabsInterface* mMenuTabsInterface;
	MessageLog* mMessageLog;

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

	void HandleActionsMenu();

	void HandleInteraction();

public:
	PlayerInterface(Player& player, Map& map);
	~PlayerInterface();

	void Update();
	void Render();
};