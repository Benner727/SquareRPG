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

std::shared_ptr<Npc> NpcFactory::GetNpc(int index)
{
	std::shared_ptr<Npc> npc;

	if (mNpcRepository.FindNpcCombatDefinition(index))
	{
		npc = std::make_shared<NpcFighter>(NpcFighter(index));

		std::dynamic_pointer_cast<NpcFighter>(npc)->mNpcCombatDefinition = mNpcRepository.FindNpcCombatDefinition(index);
		std::dynamic_pointer_cast<NpcFighter>(npc)->mNpcDropDefinition = mNpcRepository.FindNpcDropDefinition(index);
		std::dynamic_pointer_cast<NpcFighter>(npc)->Init();
	}
	else if (mNpcRepository.FindNpcShopDefinition(index))
	{
		npc = std::make_shared<NpcTrader>(NpcTrader(index));

		std::dynamic_pointer_cast<NpcTrader>(npc)->mNpcShopDefinition = mNpcRepository.FindNpcShopDefinition(index);
		std::dynamic_pointer_cast<NpcTrader>(npc)->Init();
	}
	else
		npc = std::make_shared<Npc>(Npc(index));

	npc->mNpcDefinition = mNpcRepository.FindNpcDefinition(index);
	npc->mSprite = new Square::Sprite(npc->mNpcDefinition->SpritePath());
	npc->mSprite->Parent(npc.get());

	return npc;
}