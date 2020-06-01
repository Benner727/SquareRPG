#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/Combat/MeleeFormulas.h"
#include "Game/Combat/RangedFormulas.h"
#include "Game/Combat/MagicFormulas.h"
#include "Game/Combat/CombatExperience.h"
#include "Game/Interface/MessageLog.h"

class AutoAttackCommand : public ICommand
{
private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<NpcFighter> mNpc;
	std::shared_ptr<MessageLog> mMessageLog;

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

		if (!hasAmmo)
			mMessageLog->AddMessage("With what ammo would you like to hit with?", { 0, 0, 0, 255 });

		return hasAmmo;
	}

	inline bool CanCastSpell() const
	{
		bool hasAutoCastSpell = (mPlayer->SpellBook().AutoCastSpell() != nullptr);
		bool hasRunes = (hasAutoCastSpell && mPlayer->Inventory().HasItems(mPlayer->SpellBook().AutoCastSpell()->CastReq()));

		if (!hasAutoCastSpell)
			mMessageLog->AddMessage("What spell are you trying to cast?", { 0, 0, 0, 255 });
		else if (!hasRunes)
			mMessageLog->AddMessage("How are you planning on casting that spell?", { 0, 0, 0, 255 });

		return hasRunes;
	}

public:
	AutoAttackCommand(std::shared_ptr<Player> player, std::shared_ptr<NpcFighter> npc, std::shared_ptr<MessageLog> messageLog)
	{
		mPlayer = player;
		mNpc = npc;
		mMessageLog = messageLog;
	}

	~AutoAttackCommand() = default;

	bool CanExecute()
	{
		bool canAttack = true;

		if (mPlayer->GetCombatStance().Get() == CombatOption::ranged_accurate || 
			mPlayer->GetCombatStance().Get() == CombatOption::ranged_rapid ||
			mPlayer->GetCombatStance().Get() == CombatOption::ranged_longrange)
			canAttack = HasAmmo();
		else if (mPlayer->GetCombatStance().Get() == CombatOption::magic_standard ||
			mPlayer->GetCombatStance().Get() == CombatOption::magic_defensive)
			canAttack = CanCastSpell();

		return (mNpc != nullptr) && canAttack;
	}

	void Execute()
	{
		int damage = 0;
		float attackRoll = 0.0f;
		float defenseRoll = 0.0f;

		if (mPlayer->GetCombatStance().Get() == CombatOption::ranged_accurate ||
			mPlayer->GetCombatStance().Get() == CombatOption::ranged_rapid ||
			mPlayer->GetCombatStance().Get() == CombatOption::ranged_longrange)
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
		else if (mPlayer->GetCombatStance().Get() == CombatOption::magic_standard ||
			mPlayer->GetCombatStance().Get() == CombatOption::magic_defensive)
		{
			attackRoll = MagicFormulas::AttackRoll(*mPlayer);
			defenseRoll = MagicFormulas::DefenseRoll(*mNpc);
			damage = MagicFormulas::BaseDamage(*mPlayer);

			mPlayer->Inventory().RemoveItems(mPlayer->SpellBook().AutoCastSpell()->CastReq());
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
			AddCombatExperience(mPlayer.get(), damage);
		}
		else
			damage = 0;

		mPlayer->InCombat(true);
		mPlayer->SetCombatDelay();

		mNpc->Damage(damage);
		mNpc->Target(mPlayer);
		mNpc->InCombat(true);
	}
};