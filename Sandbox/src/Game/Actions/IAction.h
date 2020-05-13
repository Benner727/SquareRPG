#pragma once

#include "Game/Commands/ICommand.h"

class IAction
{
protected:
	bool mComplete;

	void Invoke(ICommand* command)
	{
		if (command->CanExecute())
			command->Execute();
	}

public:
	IAction() : mComplete(false) {}
	virtual ~IAction() = default;

	bool Complete() const { return mComplete; }

	virtual void Update() = 0;
};