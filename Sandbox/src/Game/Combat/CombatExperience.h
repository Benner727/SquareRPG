#pragma once

#include "Game/World/Player/Player.h"

const int BASE_COMBAT_EXP = 12;
const int BASE_HITPOINTS_EXP = 4;

inline void AddCombatExperience(Player* player, int damage)
{
	player->Skills().AddExperience(Skills::SkillIndex::hitpoints, damage * BASE_HITPOINTS_EXP);

	switch (player->GetCombatStance().Get())
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
			+ player->SpellBook().AutoCastSpell()->BaseExperience());
		break;
	case CombatOption::magic_defensive:
		player->Skills().AddExperience(Skills::SkillIndex::magic, (damage * BASE_COMBAT_EXP / 3) 
			+ player->SpellBook().AutoCastSpell()->BaseExperience());
		player->Skills().AddExperience(Skills::SkillIndex::defense, damage * BASE_COMBAT_EXP / 3);
		break;
	}
}