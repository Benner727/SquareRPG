#pragma once

#include "Game/Combat/CombatFormulas.h"

inline float AttackRoll(Player& player)
{
	return HiddenRanged(player) * (2.0f + player.StatBonus().Bonus(StatBonus::RangedAttack));
}

inline float DefenseRoll(Player& player)
{
	return HiddenDefense(player) * (2.0f + player.StatBonus().Bonus(StatBonus::RangedDefense));
}

inline int RangedStrength(Player& player)
{
	int rangedStrength = 0;

	// Ranged strength will be based on the ammo used
	return rangedStrength;
}

inline float BaseDamage(Player& player)
{
	return (13.0f + HiddenRanged(player) + (RangedStrength(player) / 8.0f) +
		((HiddenRanged(player) * RangedStrength(player)) / 64.0f)) / 10.0f;
}