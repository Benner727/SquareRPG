#pragma once

#include "Game/Actions/IAction.h"
#include "Game/World/Player/Player.h"
#include "Game/World/Map/Map.h"

class WalkToPickUpAction : public IAction
{
private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<Map> mMap;

	std::shared_ptr<Square::GameObject> mTarget;

public:
	WalkToPickUpAction(std::shared_ptr<Player> player, std::shared_ptr<Map> map);

	virtual ~WalkToPickUpAction() = default;

	virtual void Update();
};