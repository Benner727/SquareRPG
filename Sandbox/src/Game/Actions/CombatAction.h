#pragma once

#include "Game/Actions/IAction.h"
#include "Game/World/Player/Player.h"
#include "Game/World/Map/PathFinder.h"
#include "Game/Npc/NpcFighter.h"
#include "Game/Interface/MessageLog.h"

class CombatAction : public IAction
{
private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<Map> mMap;
	std::shared_ptr<MessageLog> mMessageLog;

	std::shared_ptr<NpcFighter> mTarget;

	int GetRange();

	bool MoveTo(Point p);
	bool MoveInRange();

public:
	CombatAction(std::shared_ptr<Player> player, std::shared_ptr<Map> map, std::shared_ptr<MessageLog> messageLog);

	virtual ~CombatAction() = default;

	virtual void Update();
};