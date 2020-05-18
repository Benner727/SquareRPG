#include "CombatAction.h"
#include "Game/Commands/MoveInRangeCommand.h"
#include "Game/Commands/AutoAttackCommand.h"

CombatAction::CombatAction(std::shared_ptr<Player> player, std::shared_ptr<Map> map)
	: mPlayer(player), mMap(map)
{
	mTarget = std::dynamic_pointer_cast<NpcFighter>(mPlayer->Target());

	MoveInRange();
}

bool CombatAction::MoveTo(Point p)
{
	if (Tile* tile = mMap->GetCell(p)->GetTile().get())
	{
		if (tile->Walkable())
		{
			mPlayer->MoveTo(p);
			return true;
		}
	}

	return false;
}

bool CombatAction::MoveInRange()
{
	int range = 1;
	if (Weapon* weapon = dynamic_cast<Weapon*>(mPlayer->Gear().GetItem(Gear::weapon).get()))
		range = weapon->Reach();

	if (!PathFinder::InAttackRange(*mMap, mPlayer->MapPosition(), mTarget->MapPosition(), range))
		{
		if (mPlayer->CurrentPath().empty())
			{
				if (mPlayer->MapPosition() == mTarget->MapPosition())
				{
					static Point direction[4] = { {1, 0}, {-1, 0}, {0, 1}, {0 - 1} };
					for (int i = 0; i < 4; i++)
					{
						if (Tile* tile = mMap->GetCell(mPlayer->MapPosition() + direction[i])->GetTile().get())
						{
							if (tile->Walkable())
							{
								mPlayer->MoveTo(mPlayer->MapPosition() + direction[i]);
								break;
							}
						}
					}
				}
				else
				{
					int dx = mPlayer->MapPosition().x - mTarget->MapPosition().x;
					int dy = mPlayer->MapPosition().y - mTarget->MapPosition().y;

					Point p = mPlayer->MapPosition();

					if (abs(dx) > abs(dy))
						p.x -= sgn(dx);
					else
						p.y -= sgn(dy);

					if (!MoveTo(p))
						Invoke(new MoveInRangeCommand(mPlayer, mMap));
				}
			}
		}
		else
			return false;

	return true;
}

void CombatAction::Update()
{
	if (!MoveInRange() && !mPlayer->HasCombatDelay())
		Invoke(new AutoAttackCommand(mPlayer, mTarget));

	mComplete = mTarget->Dead();
}