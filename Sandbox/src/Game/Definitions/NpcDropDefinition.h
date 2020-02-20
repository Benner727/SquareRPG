#pragma once

#include <vector>

#include "WeightedDrop.h"

class NpcDropDefinition
{
private:
	int mIndex;
	std::vector<WeightedDrop> mDrops;

	NpcDropDefinition(int index, std::vector<WeightedDrop> drops)
	{
		mIndex = index;
		mDrops = drops;
	}

	~NpcDropDefinition() = default;

	friend class NpcRepository;

public:
	inline int Index() const { return mIndex; }
	inline std::vector<WeightedDrop> Drops() const { return mDrops; }
};