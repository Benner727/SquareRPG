#include "Game/Npc/NpcFactory.h"

NpcFactory& NpcFactory::Instance()
{
	static NpcFactory instance;
	return instance;
}

NpcFactory::NpcFactory()
	: mNpcRepository(NpcRepository::Instance())
{

}

NpcFactory::~NpcFactory()
{

}

Npc* NpcFactory::GetNpc(int index)
{
	Npc* npc = nullptr;

	if (mNpcRepository.FindNpcCombatDefinition(index))
	{
		npc = new NpcFighter(index);

		dynamic_cast<NpcFighter*>(npc)->mNpcCombatDefinition = mNpcRepository.FindNpcCombatDefinition(index);
		dynamic_cast<NpcFighter*>(npc)->mNpcDropDefinition = mNpcRepository.FindNpcDropDefinition(index);
		dynamic_cast<NpcFighter*>(npc)->Init();
	}
	else if (mNpcRepository.FindNpcShopDefinition(index))
	{
		npc = new NpcTrader(index);

		dynamic_cast<NpcTrader*>(npc)->mNpcShopDefinition = mNpcRepository.FindNpcShopDefinition(index);
		dynamic_cast<NpcTrader*>(npc)->Init();
	}
	else
		npc = new Npc(index);

	npc->mNpcDefinition = mNpcRepository.FindNpcDefinition(index);
	npc->mSprite = new Square::Sprite(npc->mNpcDefinition->SpritePath());
	npc->mSprite->Parent(npc);

	return npc;
}