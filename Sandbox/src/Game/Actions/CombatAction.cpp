#include "CombatAction.h"
#include "Game/Commands/MoveInRangeCommand.h"
#include "Game/Commands/AutoAttackCommand.h"

CombatAction::CombatAction(std::shared_ptr<Player> player, std::shared_ptr<Map> map)
	: mPlayer(player), mMap(map)
{
	mTarget = std::dynamic_pointer_cast<NpcFighter>(mPlayer->Target());
	mPlayer->CancelMove();
	MoveInRange();
}

int CombatAction::GetRange()
{
	int range = 1;
	if (Weapon* weapon = dynamic_cast<Weapon*>(mPlayer->Gear().GetItem(Gear::weapon).get()))
		range = weapon->Reach();

	if (mPlayer->GetCombatStance().Get() == CombatOption::magic_standard || mPlayer->GetCombatStance().Get() == CombatOption::magic_defensive)
		range = 10;
	else if (mPlayer->GetCombatStance().Get() == CombatOption::ranged_longrange)
		range += 2;

	return range;
}

bool CombatAction::MoveTo(Point p)
{
	if (mMap->TileWalkable(p))
	{
		mPlayer->MoveTo(p);
		return true;
	}

	return false;
}

bool CombatAction::MoveInRange()
{
	int range = GetRange();

	if (!PathFinder::InAttackRange(*mMap, mPlayer->MapPosition(), mTarget->MapPosition(), range))
	{
		static Point target = mTarget->MapPosition();
		if (mPlayer->CurrentPath().empty())
		{
			if (mPlayer->MapPosition() == mTarget->MapPosition())
			{
				static Point direction[4] = { {0, -1}, {1, 0}, {0, 1}, {-1, 0} };
				for (int i = 0; i < 4; i++)
				{
					if (mMap->TileWalkable(mPlayer->MapPosition() + direction[i]))
					{
						mPlayer->MoveTo(mPlayer->MapPosition() + direction[i]);
						break;
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
				{
					Invoke(new MoveInRangeCommand(mPlayer, mMap));
					target = mTarget->MapPosition();
				}
			}
		}
		else if (mPlayer->CurrentPath().size() > 1 && target != mTarget->MapPosition())
		{
			Invoke(new MoveInRangeCommand(mPlayer, mMap));
			target = mTarget->MapPosition();
		}
	}
	else
		return false;

	return true;
}

void CombatAction::Update()
{
	if (!MoveInRange() && !mPlayer->HasCombatDelay())
		mComplete = !Invoke(new AutoAttackCommand(mPlayer, mTarget));

	if (!mComplete) mComplete = mTarget->Dead();
}