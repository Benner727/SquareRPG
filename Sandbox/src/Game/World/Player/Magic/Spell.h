#pragma once

#include <Square.h>

#include "Game/Items/Item.h"

class Spell : public Square::GameObject
{
private:
	int mIndex;
	std::string mName;
	int mLevelReq;
	std::vector<std::shared_ptr<Item>> mCastReq;
	int mDamage;
	int mBaseExperience;
	bool mCanAutoCast;
	Square::Sprite* mSprite;

public:
	Spell(int index, std::string name, int levelReq, std::vector<std::shared_ptr<Item>> castReq, int damage, int baseExperience, bool canAutoCast, std::string spritePath)
	{
		mIndex = index;
		mName = name;
		mLevelReq = levelReq;
		mCastReq = castReq;
		mDamage = damage;
		mBaseExperience = baseExperience;
		mCanAutoCast = canAutoCast;

		mSprite = new Square::Sprite(spritePath);
		mSprite->Parent(this);
	}

	~Spell()
	{
		delete mSprite;
	}

	inline int Index() const { return mIndex; }
	inline std::string Name() const { return mName; }
	inline int LevelReq() const { return mLevelReq; }
	inline std::vector<std::shared_ptr<Item>> const CastReq() { return mCastReq; }
	inline int Damage() const { return mDamage; }
	inline int BaseExperience() const { return mBaseExperience; }
	inline bool CanAutoCast() const { return mCanAutoCast; }
	
	inline void Render(bool ignoreCamera = false) { mSprite->Render(ignoreCamera); }
};