#pragma once

#include "Game/Actions/IAction.h"
#include "Game/Player/Player.h"
#include "Game/Map/PathFinder.h"
#include "Game/Npc/NpcFighter.h"

class CombatAction : public IAction
{
private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<Map> mMap;

	std::shared_ptr<NpcFighter> mTarget;

public:
	CombatAction(std::shared_ptr<Player> player, std::shared_ptr<Map> map);

	virtual ~CombatAction() = default;

	virtual void Update();
};