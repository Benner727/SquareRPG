#pragma once

#include "Game/Actions/IAction.h"
#include "Game/Player/Player.h"
#include "Game/Map/Map.h"

class WalkToPickUpAction : public IAction
{
private:
	Player* mPlayer;
	Map* mMap;

	Square::GameObject* mTarget;

public:
	WalkToPickUpAction(Player* player, Map* map);

	virtual ~WalkToPickUpAction() = default;

	virtual void Update();
};