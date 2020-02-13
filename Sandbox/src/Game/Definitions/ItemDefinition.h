#pragma once

#include <string>

class ItemDefinition
{
private:
	std::string mName;
	int mIndex;
	bool mStackable;
	int mAlchemyPrice;
	int mGeneralPrice;
	std::string mSpritePath;

	ItemDefinition(std::string name, int index, bool stackable,
		int alchemyPrice, int generalPrice, std::string spritePath)
	{
		mName = name;
		mIndex = index;
		mStackable = stackable;
		mAlchemyPrice = alchemyPrice;
		mGeneralPrice = generalPrice;
		mSpritePath = spritePath;
	}

	~ItemDefinition() = default;

	friend class ItemRepository;

public:
	inline std::string Name() const { return mName; }
	inline int Index() const { return mIndex; }
	inline bool Stackable() const { return mStackable; }
	inline int AlchemyPrice() const { return mAlchemyPrice; }
	inline int GeneralPrice() const { return mGeneralPrice; }
	inline std::string SpritePath() const { return mSpritePath; }
};