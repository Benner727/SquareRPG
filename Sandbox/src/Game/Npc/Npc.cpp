#include "Game/Npc/Npc.h"

Npc::Npc(int index)
{
	mIndex = index;

	mSprite = nullptr;

	mNpcDefinition = nullptr;
}

Npc::~Npc()
{
	delete mSprite;
}

void Npc::Render()
{
	mSprite->Render();
}