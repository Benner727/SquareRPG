#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/World/Player/Player.h"
#include "Game/Items/ItemFactory.h"
#include "Game/Interface/MessageLog.h"

class UnequipCommand : public ICommand
{
private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<MessageLog> mMessageLog;

public:
	UnequipCommand(std::shared_ptr<Player> player, std::shared_ptr<MessageLog> messageLog)
	{
		mPlayer = player;
		mMessageLog = messageLog;
	}

	~UnequipCommand() = default;

	bool CanExecute()
	{
		int activeSlot = mPlayer->Gear().ActiveSlot();

		if (Equipment* equipment = dynamic_cast<Equipment*>(mPlayer->Gear().GetItem(activeSlot).get()))
		{
			if (mPlayer->Inventory().CanAdd(mPlayer->Gear().GetItem(activeSlot)))
			{
				return true;
			}
			else
			{
				mMessageLog->AddMessage("If you took that off, where would you even put it?", { 128, 128, 128, 255 });
				return false;
			}
		}

		return false;
	}

	void Execute()
	{
		int activeSlot = mPlayer->Gear().ActiveSlot();

		if (std::shared_ptr<Equipment> equipment = std::dynamic_pointer_cast<Equipment>(mPlayer->Gear().GetItem(activeSlot)))
		{
			mPlayer->Gear().SetNull(activeSlot);
			mPlayer->Inventory().Add(equipment);
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

		mPlayer->Gear().ActiveSlot(-1);
	}
};