#pragma once

#include <string>
#include <vector>

class ItemDefinition
{
private:
	std::string mName;
	int mIndex;
	bool mStackable;
	int mAlchemyPrice;
	int mGeneralPrice;
	std::string mSpritePath;
	std::vector<std::string> mInventoryActions;
	std::vector<std::string> mGroundActions;

	ItemDefinition(std::string name, int index, bool stackable,
		int alchemyPrice, int generalPrice, std::string spritePath,
		std::vector<std::string> inventoryActions, std::vector<std::string> groundActions)
	{
		mName = name;
		mIndex = index;
		mStackable = stackable;
		mAlchemyPrice = alchemyPrice;
		mGeneralPrice = generalPrice;
		mSpritePath = spritePath;
		mInventoryActions = inventoryActions;
		mGroundActions = groundActions;
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
	inline std::vector<std::string> InventoryActions() const { return mInventoryActions; }
	inline std::vector<std::string> GroundActions() const { return mGroundActions; }
};