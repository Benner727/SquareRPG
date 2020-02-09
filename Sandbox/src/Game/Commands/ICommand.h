#pragma once

class ICommand
{
public:
	virtual bool CanExecute() = 0;
	virtual void Execute() = 0;
};