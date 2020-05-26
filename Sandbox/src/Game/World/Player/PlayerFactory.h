#pragma once

#include "Game/Observers/SkillObserver.h"
#include "Game/Observers/PlayerObserver.h"

class PlayerFactory
{
private:
	std::shared_ptr<SkillObserver> mSkillObserver;
	std::shared_ptr<PlayerObserver> mPlayerObserver;

public:
	PlayerFactory();
	~PlayerFactory() = default;

	std::shared_ptr<Player> NewPlayer(std::shared_ptr<PlayerInterface>& playerUI, std::shared_ptr<Map> map, std::shared_ptr<MessageLog> messageLog, std::shared_ptr<NpcHandler> npcHandler);
};