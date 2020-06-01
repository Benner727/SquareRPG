#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/World/Player/Player.h"
#include "Game/Interface/MessageLog.h"

class SelectSpellCommand : public ICommand
{
private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<MessageLog> mMessageLog;

public:
	SelectSpellCommand(std::shared_ptr<Player> player, std::shared_ptr<MessageLog> messageLog)
	{
		mPlayer = player;
		mMessageLog = messageLog;
	}

	~SelectSpellCommand() = default;

	bool CanExecute()
	{
		bool canCast = false;
		int activeSpell = mPlayer->SpellBook().ActiveSpell();

		if (activeSpell != -1)
		{
			mPlayer->SpellBook().AutoCastSpell(-1);

			if (mPlayer->SpellBook().CombatSpells()[activeSpell]->LevelReq() <= mPlayer->Skills().GetSkills()[Skills::SkillIndex::magic]->Level())
			{
				if (mPlayer->Inventory().HasItems(mPlayer->SpellBook().CombatSpells()[activeSpell]->CastReq()))
					canCast = true;
				else
					mMessageLog->AddMessage("Try getting the correct runes before attempting to autocast that.", { 0, 0, 0, 255 });
			}
			else
				mMessageLog->AddMessage("Try training your magic level before attempting to autocast that.", { 0, 0, 0, 255 });
		}

		return canCast;
	}

	void Execute()
	{
		int activeSpell = mPlayer->SpellBook().ActiveSpell();
		mPlayer->SpellBook().AutoCastSpell(activeSpell);

		mPlayer->SpellBook().ActiveSpell(-1);
	}
};