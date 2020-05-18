#pragma once

#include "Game/Items/Item.h"

class GroundItem : public Square::GameObject
{
private:
	std::shared_ptr<Item> mItem;
	std::vector<std::string> mActions;
	float mLifeTimer;

public:
	GroundItem(std::shared_ptr<Item> item)
	{
		mItem = item;
		mItem->Parent(this);
		mItem->Pos(Square::VEC2_ZERO);

		mLifeTimer = 30.0f;

		for (const auto& action : mItem->GroundActions())
			mActions.push_back(action + " -> " + mItem->Name());
	}

	~GroundItem() = default;

	inline std::shared_ptr<Item> GetItem() const { return mItem; }
	inline std::vector<std::string> Actions() const { return mActions; }

	inline void RemoveItem()
	{
		mItem = nullptr;
		mLifeTimer = 0.0f;
	}

	inline void Expire() { mLifeTimer = 0.0f; }
	inline bool Expired() const { return (mLifeTimer <= 0.0f); }

	inline void Update() { mLifeTimer -= Square::Timer::Instance().DeltaTime(); }
	inline void Render() { if (mItem) mItem->Render(); }
};