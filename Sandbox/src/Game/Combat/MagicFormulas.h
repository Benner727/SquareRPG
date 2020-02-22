#pragma once

#include "Game/Combat/CombatFormulas.h"

inline float AttackRoll(Player& player)
{
	return HiddenMagic(player) * (2.0f + player.StatBonus().Bonus(StatBonus::MagicAttack));
}

inline float DefenseRoll(Player& player)
{
	return (HiddenDefense(player) * 0.3f + HiddenMagic(player) * 0.7f) * (2.0f + player.StatBonus().Bonus(StatBonus::MagicDefense));
}

inline float BaseDamage(Player& player)
{
	//Magic damage will be calculated based on the spell used
	return 1.0f;
}