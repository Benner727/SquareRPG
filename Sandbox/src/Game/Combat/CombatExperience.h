#pragma once

#include "Game/Player/Player.h"

const int BASE_COMBAT_EXP = 12;

inline void AddCombatExperience(Player* player, int damage)
{
	switch (player->CombatStance())
	{
	case CombatOption::melee_accurate:
		player->Skills().AddExperience(Skills::SkillIndex::attack, damage * BASE_COMBAT_EXP);
		break;
	case CombatOption::melee_aggressive:
		player->Skills().AddExperience(Skills::SkillIndex::strength, damage * BASE_COMBAT_EXP);
		break;
	case CombatOption::melee_defensive:
		player->Skills().AddExperience(Skills::SkillIndex::defense, damage * BASE_COMBAT_EXP);
		break;
	case CombatOption::melee_controlled:
		player->Skills().AddExperience(Skills::SkillIndex::attack, damage * BASE_COMBAT_EXP / 3);
		player->Skills().AddExperience(Skills::SkillIndex::strength, damage * BASE_COMBAT_EXP / 3);
		player->Skills().AddExperience(Skills::SkillIndex::defense, damage * BASE_COMBAT_EXP / 3);
		break;
	case CombatOption::ranged_accurate:
	case CombatOption::ranged_rapid:
		player->Skills().AddExperience(Skills::SkillIndex::ranged, damage * BASE_COMBAT_EXP);
		break;
	case CombatOption::ranged_longrange:
		player->Skills().AddExperience(Skills::SkillIndex::ranged, damage * BASE_COMBAT_EXP / 2);
		player->Skills().AddExperience(Skills::SkillIndex::defense, damage * BASE_COMBAT_EXP / 2);
		break;
	case CombatOption::magic_standard:
		player->Skills().AddExperience(Skills::SkillIndex::magic, (damage * BASE_COMBAT_EXP / 2) 
			+ player->SpellBook().Spells()[player->SpellBook().ActiveSpell()]->BaseExperience());
		break;
	case CombatOption::magic_defensive:
		player->Skills().AddExperience(Skills::SkillIndex::magic, (damage * BASE_COMBAT_EXP / 3) 
			+ player->SpellBook().Spells()[player->SpellBook().ActiveSpell()]->BaseExperience());
		player->Skills().AddExperience(Skills::SkillIndex::defense, damage * BASE_COMBAT_EXP / 3);
		break;
	}
}