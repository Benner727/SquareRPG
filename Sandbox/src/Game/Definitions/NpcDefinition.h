#pragma once

#include <string>
#include <vector>

class NpcDefinition
{
private:
	int mIndex;
	std::string mName;
	std::string mSpritePath;
	std::vector<std::string> mActions;

	NpcDefinition(int index, std::string name, std::string spritePath, std::vector<std::string> actions)
	{
		mIndex = index;
		mName = name;
		mSpritePath = spritePath;
		mActions = actions;
	}

	~NpcDefinition() = default;

	friend class NpcRepository;

public:
	inline int Index() const { return mIndex; }
	inline std::string Name() const { return mName; }
	inline std::string SpritePath() const { return mSpritePath; }
	inline std::vector<std::string> Actions() const { return mActions; }
};