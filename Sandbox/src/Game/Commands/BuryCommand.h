#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/World/Player/Player.h"
#include "Game/Interface/MessageLog.h"

class BuryCommand : public ICommand
{
private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<MessageLog> mMessageLog;

	bool CanBury(int itemIndex)
	{
		switch (itemIndex)
		{
		case 10: //bones
			return true;
			break;
		default:
			return false;
		}
	}

	int PrayerExperience(int itemIndex)
	{
		int experience = 0;

		switch (itemIndex)
		{
		case 10: //bones
			experience = 15;
			break;
		default:
			experience = 0;
		}

		return experience;
	}

public:
	BuryCommand(std::shared_ptr<Player> player, std::shared_ptr<MessageLog> messageLog)
	{
		mPlayer = player;
		mMessageLog = messageLog;
	}

	~BuryCommand() = default;

	bool CanExecute()
	{
		int activeSlot = mPlayer->Inventory().ActiveSlot();

		if (Item* item = dynamic_cast<Item*>(mPlayer->Inventory().GetItem(activeSlot).get()))
			return CanBury(item->Index());

		return false;
	}

	void Execute()
	{
		int activeSlot = mPlayer->Inventory().ActiveSlot();

		if (Item* item = dynamic_cast<Item*>(mPlayer->Inventory().GetItem(activeSlot).get()))
		{
			mPlayer->Skills().AddExperience(Skills::SkillIndex::prayer, PrayerExperience(item->Index()));
			mPlayer->Inventory().Remove(activeSlot);
			mMessageLog->AddMessage("You burried the bone. What are you, a dog?", { 128, 128, 128, 255 });
		}

		mPlayer->Inventory().ActiveSlot(-1);
	}
};