#pragma once

#include <map>

#include "Game/Commands/AttackCommand.h"
#include "Game/Commands/DrinkCommand.h"
#include "Game/Commands/DropCommand.h"
#include "Game/Commands/EatCommand.h"
#include "Game/Commands/EquipCommand.h"
#include "Game/Commands/UnequipCommand.h"
#include "Game/Commands/UseCommand.h"
#include "Game/Commands/TogglePrayerCommand.h"
#include "Game/Commands/CastSpellCommand.h"
#include "Game/Commands/MoveCommand.h"
#include "Game/Commands/PickUpCommand.h"
#include "Game/Commands/BuryCommand.h"
#include "Game/Commands/KillPlayerCommand.h"

class CommandManager
{
private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<Map> mMap;
	std::shared_ptr<MessageLog> mMessageLog;
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
	CommandManager(std::shared_ptr<Player> player, std::shared_ptr<Map> map, std::shared_ptr<MessageLog> messageLog)
		: mPlayer(player), mMap(map), mMessageLog(messageLog)
	{
		mCommands["Attack"] = new AttackCommand(mPlayer, mMap);
		mCommands["Drink"] = new DrinkCommand(mPlayer);
		mCommands["Drop"] = new DropCommand(mPlayer, mMap);
		mCommands["Eat"] = new EatCommand(mPlayer);
		mCommands["Equip"] = new EquipCommand(mPlayer, mMessageLog);
		mCommands["Unequip"] = new UnequipCommand(mPlayer, mMessageLog);
		mCommands["Use"] = new UseCommand(mPlayer);
		mCommands["Activate"] = new TogglePrayerCommand(mPlayer, mMessageLog);
		mCommands["Deactivate"] = new TogglePrayerCommand(mPlayer, mMessageLog);
		mCommands["Cast"] = new CastSpellCommand(mPlayer);
		mCommands["Walk Here"] = new MoveCommand(mPlayer, mMap);
		mCommands["Pick Up"] = new PickUpCommand(mPlayer, mMap, mMessageLog);
		mCommands["Bury"] = new BuryCommand(mPlayer, mMessageLog);
		mCommands["Kill Player"] = new KillPlayerCommand(mPlayer, mMap, mMessageLog);
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