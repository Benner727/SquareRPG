#pragma once

#include "Random.h"
#include "Game/Player/Player.h"
#include "Game/Npc/NpcFighter.h"

namespace CombatFormulas
{
	inline float HiddenAttack(Player& player)
	{
		float hiddenAttack = player.Skills().EffectiveLevel(Skills::attack);

		for (const auto& aura : player.PrayerBook().PrayerAuras())
		{
			if (aura.Activated())
			{
				switch (aura.Index())
				{
				case 2:
					hiddenAttack *= 1.05f;
					break;
				case 7:
					hiddenAttack *= 1.10;
					break;
				case 12:
					hiddenAttack *= 1.15f;
					break;
				case 19:
					hiddenAttack *= 1.20f;
					break;
				case 20:
					hiddenAttack *= 1.25f;
					break;
				}
			}
		}

		if (player.CombatStance() == 1) hiddenAttack += 3;
		else if (player.CombatStance() == 4) hiddenAttack += 1;

		return hiddenAttack;
	}

	inline float HiddenStrength(Player& player)
	{
		float hiddenStrength = player.Skills().EffectiveLevel(Skills::strength);

		for (const auto& aura : player.PrayerBook().PrayerAuras())
		{
			if (aura.Activated())
			{
				switch (aura.Index())
				{
				case 3:
					hiddenStrength *= 1.05f;
					break;
				case 8:
					hiddenStrength *= 1.10;
					break;
				case 13:
					hiddenStrength *= 1.15f;
					break;
				case 19:
					hiddenStrength *= 1.20f;
					break;
				case 20:
					hiddenStrength *= 1.25f;
					break;
				}
			}
		}

		if (player.CombatStance() == 2) hiddenStrength += 3;
		else if (player.CombatStance() == 4) hiddenStrength += 1;

		return hiddenStrength;
	}

	inline float HiddenDefense(Player& player)
	{
		float hiddenDefense = player.Skills().EffectiveLevel(Skills::defense);

		if (player.CombatStance() == 3) hiddenDefense += 3;
		else if (player.CombatStance() == 4) hiddenDefense += 1;

		for (const auto& aura : player.PrayerBook().PrayerAuras())
		{
			if (aura.Activated())
			{
				switch (aura.Index())
				{
				case 1:
					hiddenDefense *= 1.05f;
					break;
				case 6:
					hiddenDefense *= 1.10;
					break;
				case 11:
					hiddenDefense *= 1.15f;
					break;
				case 19:
					hiddenDefense *= 1.20f;
					break;
				case 20:
					hiddenDefense *= 1.25f;
					break;
				}
			}
		}

		return hiddenDefense;
	}

	inline float HiddenRanged(Player& player)
	{
		float hiddenRanged = player.Skills().EffectiveLevel(Skills::ranged);

		for (const auto& aura : player.PrayerBook().PrayerAuras())
		{
			if (aura.Activated())
			{
				switch (aura.Index())
				{
				case 4:
					hiddenRanged *= 1.05f;
					break;
				case 9:
					hiddenRanged *= 1.10;
					break;
				case 17:
					hiddenRanged *= 1.15f;
					break;
				}
			}
		}

		if (player.CombatStance() == 1) hiddenRanged += 3;
		else if (player.CombatStance() == 3) hiddenRanged += 1;

		return hiddenRanged;
	}

	inline float HiddenMagic(Player& player)
	{
		float hiddenMagic = player.Skills().EffectiveLevel(Skills::magic);

		for (const auto& aura : player.PrayerBook().PrayerAuras())
		{
			if (aura.Activated())
			{
				switch (aura.Index())
				{
				case 5:
					hiddenMagic *= 1.05f;
					break;
				case 10:
					hiddenMagic *= 1.10;
					break;
				case 18:
					hiddenMagic *= 1.15f;
					break;
				}
			}
		}

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
}