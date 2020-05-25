#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/World/Player/Player.h"
#include "Game/Interface/MessageLog.h"

class TogglePrayerCommand : public ICommand
{
private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<MessageLog> mMessageLog;

public:
	TogglePrayerCommand(std::shared_ptr<Player> player, std::shared_ptr<MessageLog> messageLog)
	{
		mPlayer = player;
		mMessageLog = messageLog;
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
				{
					if (mPlayer->Skills().EffectiveLevel(Skills::prayer) > 0)
					{
						return true;
					}
					else
					{
						mMessageLog->AddMessage("With what prayer points would you like to activate that aura?", { 128, 128, 128, 255 });
						return false;
					}
				}
				else
					return true;
			}
			else
			{
				mMessageLog->AddMessage("Try burying more bones before activating that aura.", { 128, 128, 128, 255 });
				return false;
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