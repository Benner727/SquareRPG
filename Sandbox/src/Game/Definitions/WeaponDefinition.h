#pragma once

class WeaponDefinition
{
private:
	int mIndex;
	bool mTwoHanded;
	float mSpeed;
	int mReach;
	bool mCasts;

	WeaponDefinition(int index, bool twoHanded, float speed, int reach, bool casts)
	{
		mIndex = index;
		mTwoHanded = twoHanded;
		mSpeed = speed;
		mReach = reach;
		mCasts = casts;
	}

	~WeaponDefinition() = default;

	friend class ItemRepository;

public:
	inline int Index() const { return mIndex; }
	inline bool TwoHanded() const { return mTwoHanded; }
	inline float Speed() const { return mSpeed; }
	inline int Reach() const { return mReach; }
	inline bool Casts() const { return mCasts; }
};