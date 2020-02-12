#pragma once

class ICommand
{
public:
	virtual ~ICommand() = default;

	virtual bool CanExecute() = 0;
	virtual void Execute() = 0;
};