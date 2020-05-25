#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/World/Player/Player.h"
#include "Game/World/Map/Map.h"
#include "Game/Interface/MessageLog.h"

class KillPlayerCommand : public ICommand
{
private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<Map> mMap;
	std::shared_ptr<MessageLog> mMessageLog;

public:
	KillPlayerCommand(std::shared_ptr<Player> player, std::shared_ptr<Map> map, std::shared_ptr<MessageLog> messageLog)
	{
		mPlayer = player;
		mMap = map;
		mMessageLog = messageLog;
	}

	~KillPlayerCommand() = default;

	bool CanExecute()
	{
		return mPlayer->Dead();
	}

	void Execute()
	{
		for (int slot = 0; slot < Inventory::INVENTORY_SIZE; slot++)
		{
			mMap->GetCell(mPlayer->MapPosition())->AddGroundItem(mPlayer->Inventory().GetItem(slot));
			mPlayer->Inventory().SetNull(slot);
		}

		for (int slot = 0; slot < Gear::GEAR_SIZE; slot++)
		{
			mMap->GetCell(mPlayer->MapPosition())->AddGroundItem(mPlayer->Gear().GetItem(slot));
			mPlayer->Gear().SetNull(slot);
		}

		mPlayer->HandleDeath();

		mMessageLog->AddMessage("You died, dumb bitch...", { 128, 0, 0, 255 });
	}
};