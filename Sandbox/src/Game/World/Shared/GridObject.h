#pragma once

#include <Square.h>

class GridObject
{
private:
	std::string mCommand;
	std::shared_ptr<Square::GameObject> mTarget;

public:
	GridObject(std::string command = "", std::shared_ptr<Square::GameObject> target = nullptr)
		: mCommand (command), mTarget(target)
	{

	}

	virtual ~GridObject() = default;

	inline std::string Command() const { return mCommand; }
	inline std::shared_ptr<Square::GameObject> Target() const { return mTarget; }
};