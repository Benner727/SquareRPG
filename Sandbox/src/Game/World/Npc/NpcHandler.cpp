#include "NpcHandler.h"

NpcHandler::NpcHandler(std::vector<std::shared_ptr<NpcController>> npcs)
{
	for (auto npc : npcs)
		AddNpc(npc);
}

void NpcHandler::AddNpc(std::shared_ptr<NpcController> npc)
{
	mNpcs[npc->GetNpc()->MapPosition()].push_back(npc);
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
				if (mNpcs[s][i]->GetNpc() != nullptr)
				{
					if (pos.x <= mNpcs[s][i]->GetNpc()->Pos().x + mNpcs[s][i]->GetNpc()->Size().x * 0.5f &&
						pos.x >= mNpcs[s][i]->GetNpc()->Pos().x - mNpcs[s][i]->GetNpc()->Size().x * 0.5f &&
						pos.y <= mNpcs[s][i]->GetNpc()->Pos().y + mNpcs[s][i]->GetNpc()->Size().y * 0.5f &&
						pos.y >= mNpcs[s][i]->GetNpc()->Pos().y - mNpcs[s][i]->GetNpc()->Size().y * 0.5f)
						npcs.push_back(mNpcs[s][i]->GetNpc());
				}
			}
		}
	}

	return npcs;
}

void NpcHandler::Update()
{
	std::vector<std::shared_ptr<NpcController>> npcList;

	for (auto& npcs : mNpcs)
	{
		for (std::vector<std::shared_ptr<NpcController>>::iterator it = npcs.second.begin(); it != npcs.second.end();)
		{
			(*it)->Update();
			if ((*it)->NewPosition())
			{
				npcList.push_back(*it);
				it = npcs.second.erase(it);
			}
			else
			{
				++it;
			}
		}
	}

	for (auto& npc : npcList)
		AddNpc(npc);
}

void NpcHandler::RenderNPC()
{
	for (auto npcs : mNpcs)
	{
		for (auto npc : npcs.second)
			npc->RenderNPC();
	}
}

void NpcHandler::RenderCombatUI()
{
	for (auto npcs : mNpcs)
	{
		for (auto npc : npcs.second)
			npc->RenderCombatUI();
	}
}