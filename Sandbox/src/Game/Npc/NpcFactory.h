#pragma once

#include <Square.h>

#include "Game/Npc/NpcRepository.h"
#include "Game/Npc/NpcFighter.h"
#include "Game/Npc/NpcTrader.h"

class NpcFactory
{
private:
	NpcRepository& mNpcRepository;

	NpcFactory();
	~NpcFactory();

public:
	static NpcFactory& Instance();

	Npc* GetNpc(int index);
};