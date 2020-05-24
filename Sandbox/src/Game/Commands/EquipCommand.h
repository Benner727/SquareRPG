#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/World/Player/Player.h"
#include "Game/Items/ItemFactory.h"

class EquipCommand : public ICommand
{
private:
	std::shared_ptr<Player> mPlayer;

public:
	EquipCommand(std::shared_ptr<Player> player)
	{
		mPlayer = player;
	}

	~EquipCommand() = default;

	bool CanExecute()
	{
		int activeSlot = mPlayer->Inventory().ActiveSlot();

		if (Equipment* equipment = dynamic_cast<Equipment*>(mPlayer->Inventory().GetItem(activeSlot).get()))
		{
			for (auto requirement : equipment->Requirements())
			{
				if (mPlayer->Skills().Level(requirement.Level()) < requirement.Level())
				{
					// Add message saying player doesn't have required level
					return false;
				}
			}

			if (Weapon* weapon = dynamic_cast<Weapon*>(equipment))
			{
				if (weapon->TwoHanded() && mPlayer->Gear().GetItem(Gear::EquipmentSlot::shield) != nullptr)
					return mPlayer->Inventory().CanAdd(mPlayer->Gear().GetItem(Gear::EquipmentSlot::shield));
			}
			else if (equipment->Slot() == Gear::EquipmentSlot::shield)
			{
				if (Weapon* weapon = dynamic_cast<Weapon*>(mPlayer->Gear().GetItem(Gear::EquipmentSlot::weapon).get()))
				{
					if (weapon->TwoHanded())
						return mPlayer->Inventory().CanAdd(mPlayer->Gear().GetItem(Gear::EquipmentSlot::weapon));
				}
			}

			return true;
		}

		return false;
	}

	void Execute()
	{
		int activeSlot = mPlayer->Inventory().ActiveSlot();

		if (std::shared_ptr<Equipment> equipment = std::dynamic_pointer_cast<Equipment>(mPlayer->Inventory().GetItem(activeSlot)))
		{
			bool unequipWeapon = false;
			bool unequipShield = false;

			if (equipment->Slot() == Gear::EquipmentSlot::shield)
			{
				if (std::shared_ptr<Weapon> weapon = std::dynamic_pointer_cast<Weapon>(mPlayer->Gear().GetItem(Gear::EquipmentSlot::weapon)))
					unequipWeapon = weapon->TwoHanded();
			}
			else if (Weapon* weapon = dynamic_cast<Weapon*>(equipment.get()))
				unequipShield = weapon->TwoHanded();

			mPlayer->Inventory().SetNull(activeSlot);
			if (std::shared_ptr<Item> unequippedSlot = mPlayer->Gear().GetItem(equipment->Slot()))
			{
				mPlayer->Inventory().Add(unequippedSlot);
				mPlayer->Gear().SetNull(equipment->Slot());
			}

			mPlayer->Gear().Add(equipment);

			if (unequipWeapon)
			{
				if (std::shared_ptr<Item> item = mPlayer->Gear().GetItem(Gear::EquipmentSlot::weapon))
				{
					mPlayer->Inventory().Add(item);
					mPlayer->Gear().SetNull(Gear::EquipmentSlot::weapon);
				}
			}
			else if (unequipShield)
			{
				if (std::shared_ptr<Item> item = mPlayer->Gear().GetItem(Gear::EquipmentSlot::shield))
				{
					mPlayer->Inventory().Add(item);
					mPlayer->Gear().SetNull(Gear::EquipmentSlot::shield);
				}
			}

			mPlayer->CalculateBonuses();
		}

		if (Weapon* weapon = dynamic_cast<Weapon*>(mPlayer->Gear().GetItem(Gear::EquipmentSlot::weapon).get()))
		{
			if (weapon->IsRanged())
				mPlayer->GetCombatStance().UpdateCombatStyle(CombatStyle::ranged);
			else if (weapon->Casts())
				mPlayer->GetCombatStance().UpdateCombatStyle(CombatStyle::magic);
			else
				mPlayer->GetCombatStance().UpdateCombatStyle(CombatStyle::melee);
		}
		else
			mPlayer->GetCombatStance().UpdateCombatStyle(CombatStyle::melee);

		mPlayer->Inventory().ActiveSlot(-1);
	}
};