#include "NpcController.h"

NpcController::NpcController(int npcIndex, Point spawnPoint, std::shared_ptr<Map> map, std::shared_ptr<Player> player)
	: mNpcIndex(npcIndex), mSpawnPoint(spawnPoint), mMap(map), mPlayer(player)
{
	mSpawnTimer = 0.0f;
	mNewPosition = false;

	SpawnNpc();
	mNpcState = NpcState::Wandering;
}

void NpcController::Invoke(ICommand* command)
{
	if (command->CanExecute())
		command->Execute();
}

void NpcController::SpawnNpc()
{
	mNpc = NpcFactory::Instance().GetNpc(mNpcIndex);
	mNpc->MapPosition(mSpawnPoint);
	mSpawnTimer = 0.0f;

	mDeathTimer = 0.6f;

	mWanderTimer = 0.0f;
	mAggressionTimer = 0.0f;

	mNewPosition = true;

	if (std::shared_ptr<NpcFighter> npcFighter = std::dynamic_pointer_cast<NpcFighter>(mNpc))
	{
		mAttackDelay = 0.0f;
		mSpawnTimer = npcFighter->RespawnTime();
	}
}

bool NpcController::NoticePlayer()
{
	std::shared_ptr<NpcFighter> npcFighter = std::dynamic_pointer_cast<NpcFighter>(mNpc);

	if (npcFighter && npcFighter->Aggressive())
	{
		if (mAggressionTimer <= 0.0f)
		{
			mAggressionTimer = 1.0f;

			float distanceFromPlayer = sqrt(pow(mPlayer->MapPosition().x - mNpc->MapPosition().x, 2) +
				pow(mPlayer->MapPosition().y - mNpc->MapPosition().y, 2) * 1.0);

			if (distanceFromPlayer <= 5.0f)
			{
				mNpc->InCombat(true);
				return true;
			}
		}
		else
			mAggressionTimer -= Square::Timer::Instance().DeltaTime();
	}

	return false;
}

void NpcController::Wander()
{
	if (!mNpc->InCombat() && mNpc->CurrentPath().empty())
	{
		if (!NoticePlayer() && mWanderTimer <= 0.0f)
		{
			if (100.0f * Random::Float() <= 33.0f)
			{
				static Point direction[4] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
				Point pos = mNpc->MapPosition() + direction[rand() % 4];

				int dx = mSpawnPoint.x - pos.x;
				int dy = mSpawnPoint.y - pos.y;

				if (abs(dx) < 11 && abs(dy) < 11)
					MoveTo(pos);
			}

			if (rand() % 2)
				mWanderTimer = 1.0f;
		}
		else
			mWanderTimer -= Square::Timer::Instance().DeltaTime();
	}
}

bool NpcController::MoveTo(Point p)
{
	if (mMap->TileWalkable(p))
	{
		mNpc->MoveTo(p);
		return true;
	}

	return false;
}

void NpcController::MoveOffPlayer()
{
	static Point direction[4] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
	for (int i = 0; i < 4; i++)
	{
		if (MoveTo(mNpc->MapPosition() + direction[i]))
			break;
	}
}

void NpcController::MoveTowardsPlayer()
{
	int dx = mNpc->MapPosition().x - mPlayer->MapPosition().x;
	int dy = mNpc->MapPosition().y - mPlayer->MapPosition().y;

	Point p = mNpc->MapPosition();
	if (abs(dx) > abs(dy))
		p.x -= sgn(dx);
	else
		p.y -= sgn(dy);

	if (!MoveTo(p))
	{
		p = mNpc->MapPosition();
		if (abs(dx) > abs(dy))
			p.y -= sgn(dy);
		else
			p.x -= sgn(dx);

		MoveTo(p);
	}
}

bool NpcController::MoveInRange()
{
	std::shared_ptr<NpcFighter> npcFighter = std::dynamic_pointer_cast<NpcFighter>(mNpc);

	if (!PathFinder::InAttackRange(*mMap, mNpc->MapPosition(), mPlayer->MapPosition(), npcFighter->AttackRange()))
	{
		if (mNpc->CurrentPath().empty())
		{
			if (mNpc->MapPosition() == mPlayer->MapPosition())
				MoveOffPlayer();
			else
				MoveTowardsPlayer();
		}

		return true;
	}

	return false;
}

void NpcController::ReturnToSpawn()
{
	static PathFinder pathFinder(*mMap);
	mNpc->PathTo(pathFinder.GeneratePath(mNpc->MapPosition(), mSpawnPoint));
	mNpc->InCombat(false);
	mNpcState = NpcState::Returning;
}

void NpcController::HandleCombat()
{
	if (mNpc->InCombat())
	{
		std::shared_ptr<NpcFighter> npcFighter = std::dynamic_pointer_cast<NpcFighter>(mNpc);

		if (mAttackDelay > 0.0f)
			mAttackDelay -= Square::Timer::Instance().DeltaTime();

		if (!MoveInRange())
		{
			if (mAttackDelay <= 0.0f)
			{
				Invoke(new NpcAttackCommand(npcFighter, mPlayer));
				mAttackDelay = npcFighter->AttackSpeed();
			}
		}

		mNpc->InCombat(!mPlayer->Dead());
	}
}

void NpcController::HandleLoot()
{
	std::shared_ptr<NpcFighter> npcFighter = std::dynamic_pointer_cast<NpcFighter>(mNpc);
	for (auto& item : NpcDropFormula::Generate(npcFighter->Drops()))
		mMap->GetCell(mNpc->MapPosition())->AddGroundItem(item);
}

void NpcController::Update()
{
	mNewPosition = false;

	if (mNpc)
	{
		Point curPos = mNpc->MapPosition();

		mNpc->Update();

		if (curPos != mNpc->MapPosition())
			mNewPosition = true;
	}

	switch (mNpcState)
	{
	case NpcState::Spawning:
		if (mSpawnTimer <= 0.0f)
		{
			SpawnNpc();
			mNpcState = NpcState::Wandering;
		}
		else
			mSpawnTimer -= Square::Timer::Instance().DeltaTime();
		break;
	case NpcState::Wandering:
		Wander();
		if (mNpc->Dead()) mNpcState = NpcState::Dead;
		else if (mNpc->InCombat()) mNpcState = NpcState::Fighting;
		break;
	case NpcState::Fighting:
		HandleCombat();
		if (mNpc->Dead()) mNpcState = NpcState::Dead;	
		else if (!mNpc->InCombat())
		{
			float distanceFromSpawn = sqrt(pow(mSpawnPoint.x - mNpc->MapPosition().x, 2) +
				pow(mSpawnPoint.y - mNpc->MapPosition().y, 2) * 1.0);

			if (distanceFromSpawn >= 11.0f)
				ReturnToSpawn();
			else
				mNpcState = NpcState::Wandering;
		}
		else
		{
			int dx = mSpawnPoint.x - mNpc->MapPosition().x;
			int dy = mSpawnPoint.y - mNpc->MapPosition().y;

			if (abs(dx) > 16 || abs(dy) > 16)
				ReturnToSpawn();
		}
		break;
	case NpcState::Returning:
		if (mNpc->CurrentPath().empty())
		{
			if (mNpc->InCombat()) mNpcState = NpcState::Fighting;
			else mNpcState = NpcState::Wandering;
		}
		if (mNpc->Dead()) mNpcState = NpcState::Dead;
		break;
	case NpcState::Dead:
		if (mDeathTimer <= 0.0f)
		{
			HandleLoot();
			mNpc.reset();
			mNpcState = NpcState::Spawning;
		}
		else
			mDeathTimer -= Square::Timer::Instance().DeltaTime();
		break;
	}
}

void NpcController::RenderNPC()
{
	if (mNpc) mNpc->Render();
}


void NpcController::RenderCombatUI()
{
	if (mNpc) mNpc->RenderHealthBar();
}