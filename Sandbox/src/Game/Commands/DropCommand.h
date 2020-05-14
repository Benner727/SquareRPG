#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/Player/Player.h"
#include "Game/Map/Map.h"

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

		if (Item* selected = dynamic_cast<Item*>(mPlayer->Inventory().GetItem(activeSlot)))
			return true;

		return false;
	}

	void Execute()
	{
		int activeSlot = mPlayer->Inventory().ActiveSlot();

		Item* item = mPlayer->Inventory().GetItem(activeSlot);
		mPlayer->Inventory().SetNull(activeSlot);
		
		mMap->GetCell(mPlayer->MapPosition())->AddGroundItem(item);

		mPlayer->Inventory().ActiveSlot(-1);
	}
};