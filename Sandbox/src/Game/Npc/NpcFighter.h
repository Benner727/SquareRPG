#pragma once

#include "Game/Npc/Npc.h"

class NpcFighter : public Npc
{
private:
	std::array<int, NpcStats::TOTAL_STATS> mStats;

	NpcCombatDefinition* mNpcCombatDefinition;
	NpcDropDefinition* mNpcDropDefinition;

	std::shared_ptr<Square::GameObject> mTarget;

	void Init()
	{
		Hitpoints(mNpcCombatDefinition->Hitpoints());
		RemainingHitpoints(Hitpoints());
		mStats = mNpcCombatDefinition->Stats();
	}

protected:

	NpcFighter(int index)
		: Npc(index)
	{	
		for (int i = 0; i < mStats.size(); i++)
			mStats[i] = 0;

		mNpcCombatDefinition = nullptr;
		mNpcDropDefinition = nullptr;
	}

	friend class NpcFactory;

public:
	~NpcFighter() = default;

	inline float RespawnTime() const { return mNpcCombatDefinition->RespawnTime(); }
	inline bool Aggressive() const { return mNpcCombatDefinition->Aggressive(); }
	inline bool Poisonous() const { return mNpcCombatDefinition->Poisonous(); }
	inline int Level() const { return mNpcCombatDefinition->Level(); }
	inline int MaxHit() const { return mNpcCombatDefinition->MaxHit(); }
	inline float AttackSpeed() const { return mNpcCombatDefinition->AttackSpeed(); }
	inline int AttackRange() const { return mNpcCombatDefinition->AttackRange(); }
	inline int CombatStyle() const { return mNpcCombatDefinition->CombatStyle(); }
	inline int Weakness() const { return mNpcCombatDefinition->Weakness(); }
	inline std::array<int, NpcStats::TOTAL_STATS> Stats() const { return mStats; }
	inline std::array<int, NpcBonus::TOTAL_BONUSES> Bonuses() const { return mNpcCombatDefinition->Bonuses(); }

	inline bool WeakTo(int flag) const { return((Weakness() & flag) == flag); }

	inline void DrainSkill(int skill, int amount) { mStats[skill] -= amount; if (mStats[skill] < 0) mStats[skill] = 0; }
	inline void BoostSkill(int skill, int amount) { mStats[skill] += amount; if (mStats[skill] > mNpcCombatDefinition->Stats()[skill]) mStats[skill] = mNpcCombatDefinition->Stats()[skill]; }
	inline void RestoreSkill(int skill) { mStats[skill] = mNpcCombatDefinition->Stats()[skill]; }

	inline std::vector<WeightedDrop> Drops() const { return (mNpcDropDefinition != nullptr ? mNpcDropDefinition->Drops() : std::vector<WeightedDrop>()); }

	inline void Target(std::shared_ptr<Square::GameObject> target) { mTarget = target; }
	inline std::shared_ptr<Square::GameObject> Target() const { return mTarget; }
};