#pragma once

#include "Game/Commands/ICommand.h"

class CommandManager
{
public:
	CommandManager() {}
	~CommandManager() = default;

	inline void Invoke(ICommand* command)
	{
		if (command)
		{
			if (command->CanExecute())
				command->Execute();

			delete command;
			command = nullptr;
		}
	}
};