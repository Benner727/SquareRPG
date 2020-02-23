#pragma once

#include "Game/Combat/CombatFormulas.h"

namespace MeleeFormulas
{
	inline float AttackRoll(Player& player)
	{
		return CombatFormulas::HiddenAttack(player) * (2.0f + player.StatBonus().Bonus(StatBonus::MeleeAttack));
	}

	inline float AttackRoll(NpcFighter& npcFighter)
	{
		return npcFighter.Stats()[NpcStats::attack] * (2.0f + npcFighter.Bonuses()[NpcBonus::MeleeAttack]);
	}

	inline float DefenseRoll(Player& player)
	{
		return CombatFormulas::HiddenDefense(player) * (2.0f + player.StatBonus().Bonus(StatBonus::MeleeDefense));
	}

	inline float DefenseRoll(NpcFighter& npcFighter)
	{
		return npcFighter.Stats()[NpcStats::defense] * (2.0f + npcFighter.Bonuses()[NpcBonus::MeleeDefense]);
	}

	inline float BaseDamage(Player& player)
	{
		return (13.0f + CombatFormulas::HiddenStrength(player) + (player.StatBonus().Bonus(StatBonus::Strength) / 8.0f) +
			((CombatFormulas::HiddenStrength(player) * player.StatBonus().Bonus(StatBonus::Strength)) / 64.0f)) / 10.0f;
	}
}