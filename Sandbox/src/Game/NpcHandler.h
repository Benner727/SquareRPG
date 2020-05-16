#pragma once

#include "Game/Npc/NpcFactory.h"

#include <map>

class NpcHandler
{
private:
	std::map<Point, std::vector<std::shared_ptr<Npc>>> mNpcs;

public:
	NpcHandler(std::vector<std::shared_ptr<Npc>> npcs = {});
	~NpcHandler() = default;

	void AddNpc(std::shared_ptr<Npc> npcs);

	std::vector<std::shared_ptr<Npc>> GetPos(Square::Vector2 pos, int z);

	void Update();
	void Render();
};