#pragma once

#include "Game/Commands/ICommand.h"

class IAction
{
protected:
	bool mComplete;

	bool Invoke(ICommand* command)
	{
		if (command->CanExecute())
		{
			command->Execute();
			return true;
		}

		return false;
	}

public:
	IAction() : mComplete(false) {}
	virtual ~IAction() = default;

	bool Complete() const { return mComplete; }

	virtual void Update() = 0;
};