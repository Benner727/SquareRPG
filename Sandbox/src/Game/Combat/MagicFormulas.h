#pragma once

#include "Game/Combat/CombatFormulas.h"

namespace MagicFormulas
{
	inline float AttackRoll(Player& player)
	{
		return CombatFormulas::HiddenMagic(player) * (2.0f + player.StatBonus().Bonus(StatBonus::MagicAttack));
	}

	inline float AttackRoll(NpcFighter& npcFighter)
	{
		return npcFighter.Stats()[NpcStats::magic] * (2.0f + npcFighter.Bonuses()[NpcBonus::MagicAttack]);
	}

	inline float DefenseRoll(Player& player)
	{
		return (CombatFormulas::HiddenDefense(player) * 0.3f + CombatFormulas::HiddenMagic(player) * 0.7f) * (2.0f + player.StatBonus().Bonus(StatBonus::MagicDefense));
	}

	inline float DefenseRoll(NpcFighter& npcFighter)
	{
		return (npcFighter.Stats()[NpcStats::defense] * 0.3f + npcFighter.Stats()[NpcStats::magic] * 0.7f) * (2.0f + npcFighter.Bonuses()[NpcBonus::MagicDefense]);
	}

	inline float BaseDamage(Player& player)
	{
		return player.SpellBook().Spells()[player.SpellBook().ActiveSpell()]->Damage();
	}
}