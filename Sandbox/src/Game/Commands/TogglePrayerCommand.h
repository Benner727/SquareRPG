#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/World/Player/Player.h"

class TogglePrayerCommand : public ICommand
{
private:
	std::shared_ptr<Player> mPlayer;

public:
	TogglePrayerCommand(std::shared_ptr<Player> player)
	{
		mPlayer = player;
	}

	~TogglePrayerCommand() = default;

	bool CanExecute()
	{
		int activeSlot = mPlayer->PrayerBook().ActiveSlot();

		if (activeSlot != -1)
		{
			if (mPlayer->Skills().Level(Skills::prayer) >= mPlayer->PrayerBook().PrayerAuras()[activeSlot]->LevelReq())
			{
				if (!mPlayer->PrayerBook().PrayerAuras()[activeSlot]->Activated())
					return (mPlayer->Skills().EffectiveLevel(Skills::prayer) > 0);
				else
					return true;
			}
		}

		return false;
	}

	void Execute()
	{
		int activeSlot = mPlayer->PrayerBook().ActiveSlot();

		if (activeSlot != -1)
			mPlayer->PrayerBook().Toggle(activeSlot);

		mPlayer->PrayerBook().ActiveSlot(-1);
	}
};