#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/Player/Player.h"
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

		if (Equipment* equipment = dynamic_cast<Equipment*>(mPlayer->Inventory().GetItem(activeSlot)))
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
				if (Weapon* weapon = dynamic_cast<Weapon*>(mPlayer->Gear().GetItem(Gear::EquipmentSlot::weapon)))
				{
					if (weapon->TwoHanded())
						return mPlayer->Inventory().CanAdd(weapon);
				}
			}

			return true;
		}

		return false;
	}

	void Execute()
	{
		int activeSlot = mPlayer->Inventory().ActiveSlot();

		if (Equipment* equipment = dynamic_cast<Equipment*>(mPlayer->Inventory().GetItem(activeSlot)))
		{
			bool unequipWeapon = false;
			bool unequipShield = false;

			if (equipment->Slot() == Gear::EquipmentSlot::shield)
			{
				if (Weapon* weapon = dynamic_cast<Weapon*>(mPlayer->Gear().GetItem(Gear::EquipmentSlot::weapon)))
					unequipWeapon = weapon->TwoHanded();
			}
			else if (Weapon* weapon = dynamic_cast<Weapon*>(mPlayer->Gear().GetItem(Gear::EquipmentSlot::weapon)))
				unequipShield = weapon->TwoHanded();

			mPlayer->Inventory().SetNull(activeSlot);
			if (Item* unequippedSlot = mPlayer->Gear().GetItem(equipment->Slot()))
			{
				mPlayer->Inventory().Add(unequippedSlot);
				mPlayer->Gear().SetNull(equipment->Slot());
			}

			mPlayer->Gear().Add(equipment);

			if (unequipWeapon)
			{
				if (Item* item = mPlayer->Gear().GetItem(Gear::EquipmentSlot::weapon))
				{
					mPlayer->Inventory().Add(item);
					mPlayer->Gear().SetNull(Gear::EquipmentSlot::weapon);
				}
			}
			else if (unequipShield)
			{
				if (Item* item = mPlayer->Gear().GetItem(Gear::EquipmentSlot::shield))
				{
					mPlayer->Inventory().Add(item);
					mPlayer->Gear().SetNull(Gear::EquipmentSlot::shield);
				}
			}

			mPlayer->CalculateBonuses();
		}

		mPlayer->Inventory().ActiveSlot(-1);
	}
};