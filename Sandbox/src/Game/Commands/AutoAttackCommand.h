#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/Combat/MeleeFormulas.h"
#include "Game/Combat/RangedFormulas.h"
#include "Game/Combat/MagicFormulas.h"
#include "Game/Combat/CombatExperience.h"

class AutoAttackCommand : public ICommand
{
private:
	Player* mPlayer;
	NpcFighter* mNpc;

	inline bool HasAmmo() const
	{
		bool hasAmmo = true;
		bool hasRangedCombatStance = 
			(mPlayer->CombatStance() == CombatOption::ranged_accurate ||
			mPlayer->CombatStance() == CombatOption::ranged_rapid ||
			mPlayer->CombatStance() == CombatOption::ranged_longrange);

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

		return hasAmmo && hasRangedCombatStance;
	}

	inline bool HasRunes() const
	{
		bool hasMagicCombatStance = (mPlayer->CombatStance() == CombatOption::magic_standard || mPlayer->CombatStance() == CombatOption::magic_defensive);
		bool hasActiveSpell = (mPlayer->SpellBook().ActiveSpell() != -1);
		bool hasRunes = mPlayer->Inventory().HasItems(mPlayer->SpellBook().Spells()[mPlayer->SpellBook().ActiveSpell()].CastReq());

		return hasMagicCombatStance && hasActiveSpell && hasRunes;
	}

public:
	AutoAttackCommand(Player* player)
	{
		mPlayer = player;
		mNpc = dynamic_cast<NpcFighter*>(player->Target());
	}

	~AutoAttackCommand() = default;

	bool CanExecute()
	{
		bool canAttack = HasAmmo() && HasRunes();

		return canAttack && (mNpc != nullptr);
	}

	void Execute()
	{
		int damage = 0;
		float attackRoll = 0.0f;
		float defenseRoll = 0.0f;

		if (HasAmmo())
		{
			attackRoll = RangedFormulas::AttackRoll(*mPlayer);
			defenseRoll = RangedFormulas::DefenseRoll(*mNpc);
			damage = RangedFormulas::BaseDamage(*mPlayer);

			if (Weapon* weapon = dynamic_cast<Weapon*>(mPlayer->Gear().GetItem(Gear::EquipmentSlot::weapon)))
			{
				if (weapon->Type() == 1)
					mPlayer->Gear().Remove(Gear::EquipmentSlot::ammo);
				else
					mPlayer->Gear().Remove(Gear::EquipmentSlot::weapon);
			}
		}
		else if (HasRunes())
		{
			attackRoll = MagicFormulas::AttackRoll(*mPlayer);
			defenseRoll = MagicFormulas::DefenseRoll(*mNpc);
			damage = MagicFormulas::BaseDamage(*mPlayer);

			mPlayer->Inventory().RemoveItems(mPlayer->SpellBook().Spells()[mPlayer->SpellBook().ActiveSpell()].CastReq());
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

			damage = std::min((int)(damage * rand.Float()) + 1, mNpc->RemainingHitpoints());
			AddCombatExperience(mPlayer, damage);
		}
		else
			damage = 0;

		mNpc->Damage(damage);
	}
};