#pragma once

#include "ICommand.h"
#include "Game/Actions/CombatAction.h"

class AttackCommand : public ICommand
{
private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<Map> mMap;

public:
	AttackCommand(std::shared_ptr<Player> player, std::shared_ptr<Map> map)
	{
		mPlayer = player;
		mMap = map;
	}

	~AttackCommand() = default;

	bool CanExecute()
	{
		return true;
	}

	void Execute()
	{
		mPlayer->SetAction(new CombatAction(mPlayer, mMap));
	}
};