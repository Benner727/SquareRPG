#pragma once

#include "Npc/NpcFactory.h"
#include "Game/Commands/MoveInRangeCommand.h"
#include "Game/Commands/NpcAttackCommand.h"
#include "Game/Utility.h"

class NpcController : public Square::GameObject
{
private:
	std::shared_ptr<Npc> mNpc;
	std::shared_ptr<Map> mMap;
	std::shared_ptr<Player> mPlayer;

	int mNpcIndex;
	Point mSpawnPoint;
	float mSpawnTimer;

	bool mInCombat;
	float mAttackDelay;

	bool mNewPosition;

	void Invoke(ICommand* command);

	void SpawnNpc();
	
	bool MoveTo(Point p);
	bool MoveInRange();

	void HandleCombat();

public:
	NpcController(int npcIndex, Point spawnPoint, std::shared_ptr<Map> map, std::shared_ptr<Player> player);
	~NpcController() = default;

	std::shared_ptr<Npc> GetNpc() const { return mNpc; }

	inline bool NewPosition() const { return mNewPosition; }

	void Update();
	void Render();
};