#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/Combat/MeleeFormulas.h"
#include "Game/Combat/RangedFormulas.h"
#include "Game/Combat/MagicFormulas.h"

class AutoAttackCommand : public ICommand
{
private:
	Player* mPlayer;
	NpcFighter* mNpc;

	inline bool HasAmmo() const
	{
		bool hasAmmo = true;

		if (mPlayer->CombatStance() == CombatOption::ranged_accurate ||
			mPlayer->CombatStance() == CombatOption::ranged_rapid ||
			mPlayer->CombatStance() == CombatOption::ranged_longrange)
		{
			if (Weapon* weapon = dynamic_cast<Weapon*>(mPlayer->Gear().GetItem(Gear::EquipmentSlot::weapon)))
			{
				if (weapon->Type() == 1)
				{
					hasAmmo = false;
					for (const auto& ammo : weapon->AmmoIndex())
					{
						if (mPlayer->Gear().HasItem(ammo))
						{
							hasAmmo = true;
							break;
						}
					}
				}
			}
		}

		return hasAmmo;
	}

	inline bool HasRunes() const
	{
		bool hasRunes = true;

		if (mPlayer->CombatStance() == CombatOption::magic_standard ||
			mPlayer->CombatStance() == CombatOption::magic_defensive)
		{
			if (mPlayer->SpellBook().ActiveSpell() != -1)
				hasRunes = mPlayer->Inventory().HasItems(mPlayer->SpellBook().Spells()[mPlayer->SpellBook().ActiveSpell()].CastReq());
		}

		return hasRunes;
	}

public:
	AutoAttackCommand(Player* player, NpcFighter* npc)
	{
		mPlayer = player;
		mNpc = npc;
	}

	~AutoAttackCommand() = default;

	bool CanExecute()
	{
		bool canAttack = HasAmmo() && HasRunes();

		return canAttack;
	}

	void Execute()
	{
		int damage = 0;
		float attackRoll = 0.0f;
		float defenseRoll = 0.0f;

		if (mPlayer->CombatStance() == CombatOption::ranged_accurate ||
			mPlayer->CombatStance() == CombatOption::ranged_rapid ||
			mPlayer->CombatStance() == CombatOption::ranged_longrange)
		{
			attackRoll = RangedFormulas::AttackRoll(*mPlayer);
			defenseRoll = RangedFormulas::DefenseRoll(*mNpc);
			damage = RangedFormulas::BaseDamage(*mPlayer);
		}
		else if (mPlayer->CombatStance() == CombatOption::magic_standard ||
			mPlayer->CombatStance() == CombatOption::magic_defensive)
		{
			attackRoll = MagicFormulas::AttackRoll(*mPlayer);
			defenseRoll = MagicFormulas::DefenseRoll(*mNpc);
			damage = MagicFormulas::BaseDamage(*mPlayer);
		}
		else
		{
			attackRoll = MeleeFormulas::AttackRoll(*mPlayer);
			defenseRoll = MeleeFormulas::DefenseRoll(*mNpc);
			damage = MeleeFormulas::BaseDamage(*mPlayer);
		}

		if (CombatFormulas::AccurateHit(attackRoll, defenseRoll))
		{
			Random rand;
			rand.Init();

			damage = (int)(damage * rand.Float()) + 1;
		}
		else
			damage = 0;

		mNpc->Damage(damage);
	}
};