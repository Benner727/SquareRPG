#include "Game/Npc/Npc.h"

Npc::Npc(int index)
{
	mIndex = index;

	mSprite = nullptr;

	mNpcDefinition = nullptr;

	std::cout << "Created" << std::endl;
}

Npc::~Npc()
{
	delete mSprite;

	std::cout << "Deleted" << std::endl;
}

void Npc::Render()
{
	mSprite->Render();
}