#pragma once

#include <Square.h>

class GridObject
{
private:
	std::string mCommand;
	Square::GameObject* mTarget;

public:
	GridObject(std::string command = "", Square::GameObject* target = nullptr)
		: mCommand (command), mTarget(target)
	{

	}

	virtual ~GridObject() = default;

	inline std::string Command() const { return mCommand; }
	inline Square::GameObject* Target() const { return mTarget; }
};