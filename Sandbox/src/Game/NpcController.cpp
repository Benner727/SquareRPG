#include "NpcController.h"

NpcController::NpcController(int npcIndex, Point spawnPoint, std::shared_ptr<Map> map, std::shared_ptr<Player> player)
	: mNpcIndex(npcIndex), mSpawnPoint(spawnPoint), mMap(map), mPlayer(player)
{
	mSpawnTimer = 0.0f;
	mInCombat = false;
	mNewPosition = false;

	SpawnNpc();
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

	if (std::shared_ptr<NpcFighter> npcFighter = std::dynamic_pointer_cast<NpcFighter>(mNpc))
	{
		mAttackDelay = npcFighter->AttackSpeed();
		mSpawnTimer = npcFighter->RespawnTime();
	}
}

bool NpcController::MoveTo(Point p)
{
	if (Tile* tile = mMap->GetCell(p)->GetTile().get())
	{
		if (tile->Walkable())
		{
			mNpc->MoveTo(p);
			return true;
		}
	}

	return false;
}

bool NpcController::MoveInRange()
{
	if (std::shared_ptr<NpcFighter> npcFighter = std::dynamic_pointer_cast<NpcFighter>(mNpc))
	{
		if (!PathFinder::InAttackRange(*mMap, mNpc->MapPosition(), mPlayer->MapPosition(), npcFighter->AttackRange()))
		{
			if (mNpc->CurrentPath().empty())
			{
				if (mNpc->MapPosition() == mPlayer->MapPosition())
				{
					static Point direction[4] = { {1, 0}, {-1, 0}, {0, 1}, {0 - 1} };
					for (int i = 0; i < 4; i++)
					{
						if (Tile* tile = mMap->GetCell(mNpc->MapPosition() + direction[i])->GetTile().get())
						{
							if (tile->Walkable())
							{
								mNpc->MoveTo(mNpc->MapPosition() + direction[i]);
								break;
							}
						}
					}
				}
				else
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
			}
		}
		else
			return false;
	}

	return true;
}

void NpcController::HandleCombat()
{
	mInCombat = (std::dynamic_pointer_cast<NpcFighter>(mNpc)->Target() != nullptr);

	if (mInCombat)
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
	}
}

void NpcController::Update()
{
	mNewPosition = false;

	if (mNpc)
	{
		Point curPos = mNpc->MapPosition();

		HandleCombat();
		mNpc->Update();

		if (mNpc->Dead())
		{
			mNpc.reset();
		}
		else
			mNewPosition = (curPos == mNpc->MapPosition());
	}
	else if (mSpawnTimer > 0.0f)
		mSpawnTimer -= Square::Timer::Instance().DeltaTime();
	else
		SpawnNpc();
}

void NpcController::Render()
{
	if (mNpc) mNpc->Render();
}
