#include "CombatAction.h"
#include "Game/Commands/MoveInRangeCommand.h"
#include "Game/Commands/AutoAttackCommand.h"

CombatAction::CombatAction(std::shared_ptr<Player> player, std::shared_ptr<Map> map)
	: mPlayer(player), mMap(map)
{
	mTarget = std::dynamic_pointer_cast<NpcFighter>(mPlayer->Target());

	int range = 1;
	if (Weapon* weapon = dynamic_cast<Weapon*>(mPlayer->Gear().GetItem(Gear::weapon).get()))
		range = weapon->Reach();

	if (!PathFinder::InAttackRange(*mMap, mPlayer->MapPosition(), mTarget->MapPosition(), range))
		Invoke(new MoveInRangeCommand(mPlayer, mMap));
}

void CombatAction::Update()
{
	if (mPlayer->CurrentPath().empty())
	{
		if (!mPlayer->HasCombatDelay())
			Invoke(new AutoAttackCommand(mPlayer, mTarget));

		mComplete = mTarget->Dead();
	}
}
