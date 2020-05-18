#pragma once

#include "Game/NpcController.h"

#include <map>

class NpcHandler
{
private:
	std::map<Point, std::vector<std::shared_ptr<NpcController>>> mNpcs;

public:
	NpcHandler(std::vector<std::shared_ptr<NpcController>> npcs = {});
	~NpcHandler() = default;

	void AddNpc(std::shared_ptr<NpcController> npcs);

	std::vector<std::shared_ptr<Npc>> GetPos(Square::Vector2 pos, int z);

	void Update();
	void Render();
};