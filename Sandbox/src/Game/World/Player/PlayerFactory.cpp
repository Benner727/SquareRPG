#include "PlayerFactory.h"

PlayerFactory::PlayerFactory()
{
}

std::shared_ptr<Player> PlayerFactory::NewPlayer(std::shared_ptr<PlayerInterface>& playerUI, std::shared_ptr<Map> map, std::shared_ptr<MessageLog> messageLog, std::shared_ptr<NpcHandler> npcHandler)
{
	std::shared_ptr<Player> player = std::make_shared<Player>(Point(6, 2, 0));

	playerUI = std::make_shared<PlayerInterface>(player, messageLog, map, npcHandler);

	mSkillObserver = std::make_shared<SkillObserver>(messageLog);

	for (auto& skill : player->Skills().GetSkills())
		skill->RegisterObserver(mSkillObserver);

	mPlayerObserver = std::make_shared<PlayerObserver>(playerUI, map, messageLog);
	player->RegisterObserver(mPlayerObserver);

	// To be removed
	for (int i = 1; i < 10; i++)
	{
		player->Inventory().Add(ItemFactory::Instance().GetItem(i));
	}

	return player;
}
