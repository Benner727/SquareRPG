#pragma once

#include "Random.h"
#include "Game/Player/Player.h"
#include "Game/Npc/NpcFighter.h"

inline float HiddenAttack(Player& player)
{
	float hiddenAttack = player.Skills().EffectiveLevel(Skills::attack);

	if (player.CombatStance() == 1) hiddenAttack += 3;
	else if (player.CombatStance() == 4) hiddenAttack += 1;

	return hiddenAttack;
}

inline float HiddenStrength(Player& player)
{
	float hiddenStrength = player.Skills().EffectiveLevel(Skills::strength);

	if (player.CombatStance() == 2) hiddenStrength += 3;
	else if (player.CombatStance() == 4) hiddenStrength += 1;

	return hiddenStrength;
}

inline float HiddenDefense(Player& player)
{
	float hiddenDefense = player.Skills().EffectiveLevel(Skills::defense);

	if (player.CombatStance() == 3) hiddenDefense += 3;
	else if (player.CombatStance() == 4) hiddenDefense += 1;

	return hiddenDefense;
}

inline float HiddenRanged(Player& player)
{
	float hiddenRanged = player.Skills().EffectiveLevel(Skills::ranged);

	if (player.CombatStance() == 1) hiddenRanged += 3;
	else if (player.CombatStance() == 3) hiddenRanged += 1;

	return hiddenRanged;
}

inline float HiddenMagic(Player& player)
{
	float hiddenMagic = player.Skills().EffectiveLevel(Skills::magic);

	if (player.CombatStance() == 1) hiddenMagic += 3;
	else if (player.CombatStance() == 2) hiddenMagic += 1;

	return hiddenMagic;
}

inline float HitChance(float attack, float defence)
{
	float A = attack,
		D = defence;

	float chance = A < D ? (A - 1.0f) / (2.0f * D) : 1.0f - (D + 1.0f) / (2.0f * A);
	chance = chance > 0.9999f ? 0.9999f : chance < 0.0001f ? 0.0001f : chance;

	return chance;
}

inline bool AccurateHit(float attack, float defense)
{
	Random rand;
	rand.Init();

	float chance = HitChance(attack, defense);
	return (rand.Float() <= chance);
}