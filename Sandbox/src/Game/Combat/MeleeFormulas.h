#pragma once

#include "Game/Combat/CombatFormulas.h"

inline float AttackRoll(Player& player)
{
	return HiddenAttack(player) * (2.0f + player.StatBonus().Bonus(StatBonus::MeleeAttack));
}

inline float DefenseRoll(Player& player)
{
	return HiddenDefense(player) * (2.0f + player.StatBonus().Bonus(StatBonus::MeleeDefense));
}

inline float BaseDamage(Player& player)
{
	return (13.0f + HiddenStrength(player) + (player.StatBonus().Bonus(StatBonus::Strength) / 8.0f) + 
		((HiddenStrength(player) * player.StatBonus().Bonus(StatBonus::Strength)) / 64.0f)) / 10.0f;
}