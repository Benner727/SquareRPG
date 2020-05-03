#pragma once

#include "Game/Commands/ICommand.h"
#include "Game/Player/Player.h"
#include "Game/Npc/NpcFighter.h"

class CastSpellCommand : public ICommand
{
private:
	Player* mPlayer;
	NpcFighter* mNpc;

public:
	CastSpellCommand(Player* player)
	{
		mPlayer = player;
		mNpc = dynamic_cast<NpcFighter*>(player->Target());
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