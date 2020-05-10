#pragma once

#include <map>

#include "Game/Commands/AutoAttackCommand.h"
#include "Game/Commands/DrinkCommand.h"
#include "Game/Commands/DropCommand.h"
#include "Game/Commands/EatCommand.h"
#include "Game/Commands/EquipCommand.h"
#include "Game/Commands/UnequipCommand.h"
#include "Game/Commands/UseCommand.h"
#include "Game/Commands/TogglePrayerCommand.h"
#include "Game/Commands/CastSpellCommand.h"
#include "Game/Commands/MoveCommand.h"

class CommandManager
{
private:
	Player* mPlayer;
	Map* mMap;
	std::map<std::string, ICommand*> mCommands;

	inline void Invoke(ICommand* command)
	{
		if (command)
		{
			if (command->CanExecute())
				command->Execute();
			else
			{
				//Fix this
				mPlayer->Inventory().ActiveSlot(-1);
				mPlayer->SpellBook().ActiveSpell(-1);
				mPlayer->Target(nullptr);
			}
		}
	}

public:
	CommandManager(Player* player, Map* map)
		: mPlayer(player), mMap(map)
	{
		mCommands["Attack"] = new AutoAttackCommand(mPlayer);
		mCommands["Drink"] = new DrinkCommand(mPlayer);
		mCommands["Drop"] = new DropCommand(mPlayer);
		mCommands["Eat"] = new EatCommand(mPlayer);
		mCommands["Equip"] = new EquipCommand(mPlayer);
		mCommands["Unequip"] = new UnequipCommand(mPlayer);
		mCommands["Use"] = new UseCommand(mPlayer);
		mCommands["Activate"] = new TogglePrayerCommand(mPlayer);
		mCommands["Deactivate"] = new TogglePrayerCommand(mPlayer);
		mCommands["Cast"] = new CastSpellCommand(mPlayer);
		mCommands["Walk Here"] = new MoveCommand(mPlayer, mMap);
	}
	
	~CommandManager()
	{
		for (auto command : mCommands)
			delete command.second;
	}

	inline void Invoke(std::string command)
	{
		Invoke(mCommands[command]);
	}
};