#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/Combat/MeleeFormulas.h"
#include "Game/Combat/RangedFormulas.h"
#include "Game/Combat/MagicFormulas.h"
#include "Game/Combat/CombatExperience.h"

class NpcAttackCommand : public ICommand
{
private:
	std::shared_ptr<NpcFighter> mNpc;
	std::shared_ptr<Player> mPlayer;

public:
	NpcAttackCommand(std::shared_ptr<NpcFighter> npc, std::shared_ptr<Player> player)
	{
		mNpc = npc;
		mPlayer = player;
	}

	~NpcAttackCommand() = default;

	bool CanExecute()
	{
		return true;
	}

	void Execute()
	{
		int damage = 0;
		float attackRoll = 0.0f;
		float defenseRoll = 0.0f;

		if (mNpc->CombatStyle() == (int)CombatStyle::ranged)
		{
			attackRoll = RangedFormulas::AttackRoll(*mNpc);
			defenseRoll = RangedFormulas::DefenseRoll(*mPlayer);
		}
		else if (mNpc->CombatStyle() == (int)CombatStyle::magic)
		{
			attackRoll = MagicFormulas::AttackRoll(*mNpc);
			defenseRoll = MagicFormulas::DefenseRoll(*mPlayer);
		}
		else if (mNpc->CombatStyle() == (int)CombatStyle::melee)
		{
			attackRoll = MeleeFormulas::AttackRoll(*mNpc);
			defenseRoll = MeleeFormulas::DefenseRoll(*mPlayer);
		}

		if (CombatFormulas::AccurateHit(attackRoll, defenseRoll))
		{
			Random rand;
			rand.Init();

			damage = std::min((int)((float)mNpc->MaxHit() * rand.Float()) + 1, mPlayer->Skills().EffectiveLevel(Skills::SkillIndex::hitpoints));
		}

		mPlayer->InCombat(true);
		mPlayer->Damage(damage);

		mNpc->InCombat(true);
	}
};