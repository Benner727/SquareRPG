#include "NpcHandler.h"

NpcHandler::NpcHandler(std::vector<std::shared_ptr<Npc>> npcs)
{
	for (auto npc : npcs)
		AddNpc(npc);
}

void NpcHandler::AddNpc(std::shared_ptr<Npc> npc)
{
	mNpcs[npc->MapPosition()].push_back(npc);
}

std::vector<std::shared_ptr<Npc>> NpcHandler::GetPos(Square::Vector2 pos, int z)
{
	Point p(pos, z);
	std::vector<std::shared_ptr<Npc>> npcs;
	npcs.clear();

	for (int y = -1; y <= 1; y++)
	{
		for (int x = -1; x <= 1; x++)
		{
			Point s = p;
			s.x += x;
			s.y += y;
			for (int i = 0; i < mNpcs[s].size(); i++)
			{
				if (pos.x <= mNpcs[s][i]->Pos().x + mNpcs[s][i]->Size().x * 0.5f &&
					pos.x >= mNpcs[s][i]->Pos().x - mNpcs[s][i]->Size().x * 0.5f &&
					pos.y <= mNpcs[s][i]->Pos().y + mNpcs[s][i]->Size().y * 0.5f &&
					pos.y >= mNpcs[s][i]->Pos().y - mNpcs[s][i]->Size().y * 0.5f)
					npcs.push_back(mNpcs[s][i]);
			}
		}
	}

	return npcs;
}

void NpcHandler::Update()
{
	for (auto& npcs : mNpcs)
	{
		for (std::vector<std::shared_ptr<Npc>>::iterator it = npcs.second.begin(); it != npcs.second.end();)
		{
			if ((*it)->Dead())
			{
				it = npcs.second.erase(it);
			}
			else
			{
				(*it)->Update();
				++it;
			}
		}
	}
}

void NpcHandler::Render()
{
	for (auto npcs : mNpcs)
	{
		for (auto npc : npcs.second)
			npc->Render();
	}
}
