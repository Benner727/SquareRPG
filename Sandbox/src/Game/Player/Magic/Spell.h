#pragma once

#include <Square.h>

#include "Game/Items/Item.h"

class Spell : public Square::GameObject
{
private:
	int mIndex;
	std::string mName;
	int mLevelReq;
	std::vector<Item*> mCastReq;
	int mDamage;
	int mBaseExperience;
	Square::Sprite* mSprite;

public:
	Spell(int index, std::string name, int levelReq, std::vector<Item*> castReq, int damage, int baseExperience, std::string spritePath)
	{
		mIndex = index;
		mName = name;
		mLevelReq = levelReq;
		mCastReq = castReq;
		mDamage = damage;
		mBaseExperience = baseExperience;

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
	inline std::vector<Item*> const CastReq() { return mCastReq; }
	inline int Damage() const { return mDamage; }
	inline int BaseExperience() const { return mBaseExperience; }
	
	inline void Render(bool ignoreCamera = false) { mSprite->Render(ignoreCamera); }
};