#pragma once

#include <array>

enum class CombatStyle : uint8_t
{
	none = 0x00,
	melee = 0x01,
	ranged = 0x02,
	magic = 0x04
};

enum NpcStats
{
	attack, strength, defense, magic, ranged, TOTAL_STATS
};

enum NpcBonus
{
	MeleeAttack, MagicAttack, RangedAttack,
	MeleeDefense, MagicDefense, RangedDefense,
	TOTAL_BONUSES
};

class NpcCombatDefinition
{
private:
	int mIndex;
	float mRespawnTime;
	bool mAggressive;
	bool mPoisonous;
	int mLevel;
	int mHitpoints;
	int mMaxHit;
	float mAttackSpeed;
	int mCombatStyle;
	int mWeakness;
	std::array<int, NpcStats::TOTAL_STATS> mStats;
	std::array<int, NpcBonus::TOTAL_BONUSES> mBonuses;

	NpcCombatDefinition(int index, float respawnTime, bool aggressive, 
		bool poisonous, int level, int hitpoints, int maxHit, 
		float attackSpeed, int combatStyles, int weakness,
		std::array<int, NpcStats::TOTAL_STATS> stats, std::array<int, NpcBonus::TOTAL_BONUSES> bonuses)
	{
		mIndex = index;
		mRespawnTime = respawnTime;
		mAggressive = aggressive;
		mPoisonous = poisonous;
		mLevel = level;
		mHitpoints = hitpoints;
		mMaxHit = maxHit;
		mAttackSpeed = attackSpeed;
		mCombatStyle = combatStyles;
		mWeakness = weakness;
		mStats = stats;
		mBonuses = bonuses;
	}

	~NpcCombatDefinition() = default;

	friend class NpcRepository;

public:
	inline int Index() const { return mIndex; }
	inline float RespawnTime() const { return mRespawnTime; }
	inline bool Aggressive() const { return mAggressive; }
	inline bool Poisonous() const { return mPoisonous; }
	inline int Level() const { return mLevel; }
	inline int Hitpoints() const { return mHitpoints; }
	inline int MaxHit() const { return mMaxHit; }
	inline float AttackSpeed() const { return mAttackSpeed; }
	inline int CombatStyle() const { return mCombatStyle; }
	inline int Weakness() const { return mWeakness; }
	inline std::array<int, NpcStats::TOTAL_STATS> Stats() const { return mStats; }
	inline std::array<int, NpcBonus::TOTAL_BONUSES> Bonuses() const { return mBonuses; }
};