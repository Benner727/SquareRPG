#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/Player/Player.h"
#include "Game/Npc/NpcFighter.h"

class CastSpellCommand : public ICommand
{
private:
	std::shared_ptr<Player> mPlayer;
	std::shared_ptr<NpcFighter> mNpc;

public:
	CastSpellCommand(std::shared_ptr<Player> player)
	{
		mPlayer = player;
		//mNpc = std::dynamic_pointer_cast<NpcFighter>(player->Target());
	}

	~CastSpellCommand() = default;

	bool CanExecute()
	{
		bool canAttack = false;

		return canAttack && (mNpc != nullptr);
	}

	void Execute()
	{
		mPlayer->SpellBook().ActiveSpell(-1);
		mPlayer->Target(nullptr);
	}
};