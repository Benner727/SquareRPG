#pragma once

#include "Npc/NpcFactory.h"
#include "Npc/NpcDropFormula.h"
#include "Game/Commands/MoveInRangeCommand.h"
#include "Game/Commands/NpcAttackCommand.h"
#include "Game/Utility.h"

class NpcController
{
private:
	enum class NpcState {};

	std::shared_ptr<Npc> mNpc;
	std::shared_ptr<Map> mMap;
	std::shared_ptr<Player> mPlayer;

	int mNpcIndex;
	Point mSpawnPoint;
	float mSpawnTimer;

	float mDeathTimer;

	float mWanderTimer;

	float mAttackDelay;

	bool mNewPosition;

	void Invoke(ICommand* command);

	void SpawnNpc();
	
	void Wander();

	bool MoveTo(Point p);
	bool MoveInRange();

	void HandleCombat();
	void HandleLoot();

public:
	NpcController(int npcIndex, Point spawnPoint, std::shared_ptr<Map> map, std::shared_ptr<Player> player);
	~NpcController() = default;

	std::shared_ptr<Npc> GetNpc() const { return mNpc; }

	inline bool NewPosition() const { return mNewPosition; }

	void Update();

	void RenderNPC();
	void RenderCombatUI();
};