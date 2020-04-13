#pragma once

#include <Square.h>

#include <string>

enum class AuraType { attack, strength, defense, combat, mage_range, over_head, utility };

class Aura : public Square::GameObject
{
private:
	int mIndex;
	std::string mName;
	int mLevelReq;
	float mDrainRate;
	AuraType mAuraType;
	bool mActivated;
	Square::Sprite* mSprite;

public:
	Aura(int index, std::string name, int levelReq, float drainRate, AuraType auraType, std::string spritePath)
	{
		mIndex = index;
		mName = name;
		mLevelReq = levelReq;
		mDrainRate = drainRate;
		mAuraType = auraType;
		
		mActivated = false;

		mSprite = new Square::Sprite(spritePath);
		mSprite->Parent(this);
	}

	~Aura()
	{
		delete mSprite;
	}

	inline int Index() const { return mIndex; }
	inline std::string Name() const { return mName; }
	inline int LevelReq() const { return mLevelReq; }
	inline float DrainRate() const { return mDrainRate; }
	inline AuraType AuraType() const { return mAuraType; }

	inline bool Activated() const { return mActivated; }
	inline void Activated(bool activated) { mActivated = activated; }

	inline void Render() { mSprite->Render(); }
};