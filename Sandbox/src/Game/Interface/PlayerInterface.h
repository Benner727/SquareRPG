#pragma once

#include "Game/Commands/CommandManager.h"
#include "Game/Interface/MenuTabsInterface.h"
#include "Game/GameGrid.h"
#include "Game/Interface/MessageLog.h"

class PlayerInterface : public Square::GameObject
{
private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<Map> mMap;

	GameGrid mGameGrid;

	MenuTabsInterface* mMenuTabsInterface;
	MessageLog* mMessageLog;

	CommandManager mCommandManager;
	std::string mCommand;

	bool mWaitingForInteraction;

	std::string mHoverText;
	Square::Text* mHoverSprite;

	ActionsMenu* mActionsMenu;

	std::shared_ptr<Square::GameObject> mTargetObject;

	void SetHoverText();

	void HandleUse();
	void HandleCast();

	void HandleActionsMenu();

	void HandleInteraction();

public:
	PlayerInterface(std::shared_ptr<Player> player, std::shared_ptr<Map> map);
	~PlayerInterface();

	void Update();
	void Render();
};