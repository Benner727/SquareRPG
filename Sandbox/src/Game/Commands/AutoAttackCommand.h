#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/Combat/MeleeFormulas.h"
#include "Game/Combat/RangedFormulas.h"
#include "Game/Combat/MagicFormulas.h"
#include "Game/Combat/CombatExperience.h"

class AutoAttackCommand : public ICommand
{
private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<NpcFighter> mNpc;

	inline bool HasAmmo() const
	{
		bool hasAmmo = false;

		if (Weapon* weapon = dynamic_cast<Weapon*>(mPlayer->Gear().GetItem(Gear::EquipmentSlot::weapon).get()))
		{
			if (weapon->Type() == 1)
			{
				for (const auto& ammo : weapon->AmmoIndex())
				{
					if (mPlayer->Gear().HasItem(ammo))
					{
						hasAmmo = true;
						break;
					}
				}
			}
			else
				hasAmmo = true;
		}

		return hasAmmo;
	}

	inline bool CanCastSpell() const
	{
		bool hasAutoCastSpell = (mPlayer->SpellBook().AutoCastSpell() != nullptr);
		bool hasRunes = (hasAutoCastSpell && mPlayer->Inventory().HasItems(mPlayer->SpellBook().AutoCastSpell()->CastReq()));

		return hasRunes;
	}

public:
	AutoAttackCommand(std::shared_ptr<Player> player, std::shared_ptr<NpcFighter> npc)
	{
		mPlayer = player;
		mNpc = npc;
	}

	~AutoAttackCommand() = default;

	bool CanExecute()
	{
		bool canAttack = true;

		if (mPlayer->GetCombatStance().GetCombatStyle() == CombatStyle::ranged)
			canAttack = HasAmmo();
		else if (mPlayer->GetCombatStance().GetCombatStyle() == CombatStyle::magic)
			canAttack = CanCastSpell();

		return (mNpc != nullptr) && canAttack;
	}

	void Execute()
	{
		int damage = 0;
		float attackRoll = 0.0f;
		float defenseRoll = 0.0f;

		if (mPlayer->GetCombatStance().GetCombatStyle() == CombatStyle::ranged)
		{
			attackRoll = RangedFormulas::AttackRoll(*mPlayer);
			defenseRoll = RangedFormulas::DefenseRoll(*mNpc);
			damage = RangedFormulas::BaseDamage(*mPlayer);

			if (Weapon* weapon = dynamic_cast<Weapon*>(mPlayer->Gear().GetItem(Gear::EquipmentSlot::weapon).get()))
			{
				if (weapon->Type() == 1)
					mPlayer->Gear().Remove(Gear::EquipmentSlot::ammo);
				else
					mPlayer->Gear().Remove(Gear::EquipmentSlot::weapon);
			}
		}
		else if (mPlayer->GetCombatStance().GetCombatStyle() == CombatStyle::magic)
		{
			attackRoll = MagicFormulas::AttackRoll(*mPlayer);
			defenseRoll = MagicFormulas::DefenseRoll(*mNpc);
			damage = MagicFormulas::BaseDamage(*mPlayer);

			mPlayer->Inventory().RemoveItems(mPlayer->SpellBook().Spells()[mPlayer->SpellBook().ActiveSpell()]->CastReq());
		}
		else if (mPlayer->GetCombatStance().GetCombatStyle() == CombatStyle::melee)
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
			AddCombatExperience(mPlayer.get(), damage);
		}
		else
			damage = 0;

		mPlayer->InCombat(true);
		mPlayer->SetCombatDelay();
		mNpc->Damage(damage);

		std::cout << mNpc->RemainingHitpoints() << "/" << mNpc->Hitpoints() << std::endl;
	}
};