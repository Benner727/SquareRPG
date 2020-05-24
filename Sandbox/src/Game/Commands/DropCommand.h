#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/World/Player/Player.h"
#include "Game/World/Map/Map.h"

class DropCommand : public ICommand
{
private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<Map> mMap;

public:
	DropCommand(std::shared_ptr<Player> player, std::shared_ptr<Map> map)
	{
		mPlayer = player;
		mMap = map;
	}

	~DropCommand() = default;

	bool CanExecute()
	{
		int activeSlot = mPlayer->Inventory().ActiveSlot();

		if (Item* selected = dynamic_cast<Item*>(mPlayer->Inventory().GetItem(activeSlot).get()))
			return true;

		return false;
	}

	void Execute()
	{
		int activeSlot = mPlayer->Inventory().ActiveSlot();

		mMap->GetCell(mPlayer->MapPosition())->AddGroundItem(mPlayer->Inventory().GetItem(activeSlot));
		mPlayer->Inventory().SetNull(activeSlot);

		mPlayer->Inventory().ActiveSlot(-1);
	}
};