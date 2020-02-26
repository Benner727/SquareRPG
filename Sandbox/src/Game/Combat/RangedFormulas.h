#pragma once

#include "Game/Combat/CombatFormulas.h"
#include "Game/Items/Weapon.h"

namespace RangedFormulas
{
	inline float AttackRoll(Player& player)
	{
		return CombatFormulas::HiddenRanged(player) * (2.0f + player.StatBonus().Bonus(StatBonus::RangedAttack));
	}

	inline float AttackRoll(NpcFighter& npcFighter)
	{
		return npcFighter.Stats()[NpcStats::ranged] * (2.0f + npcFighter.Bonuses()[NpcBonus::RangedAttack]);
	}

	inline float DefenseRoll(Player& player)
	{
		return CombatFormulas::HiddenDefense(player) * (2.0f + player.StatBonus().Bonus(StatBonus::RangedDefense));
	}

	inline float DefenseRoll(NpcFighter& npcFighter)
	{
		return npcFighter.Stats()[NpcStats::defense] * (2.0f + npcFighter.Bonuses()[NpcBonus::RangedDefense]);
	}

	inline int RangedStrength(Player& player)
	{
		int rangedStrength = 0;

		if (Weapon* weapon = dynamic_cast<Weapon*>(player.Gear().GetItem(Gear::EquipmentSlot::weapon)))
		{
			if (weapon->Type() == 1)
			{
				switch (weapon->Index())
				{
					// To do
				}
			}
			else if (Equipment* ammo = dynamic_cast<Equipment*>(player.Gear().GetItem(Gear::EquipmentSlot::ammo)))
			{
				switch (ammo->Index())
				{
					// To do
				}
			}
		}

		return rangedStrength;
	}

	inline float BaseDamage(Player& player)
	{
		return (13.0f + CombatFormulas::HiddenRanged(player) + (RangedStrength(player) / 8.0f) +
			((CombatFormulas::HiddenRanged(player) * RangedStrength(player)) / 64.0f)) / 10.0f;
	}
}