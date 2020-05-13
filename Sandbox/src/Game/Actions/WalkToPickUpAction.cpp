#include "WalkToPickUpAction.h"

#include "Game/Commands/MoveCommand.h"
#include "Game/Commands/PickUpCommand.h"

WalkToPickUpAction::WalkToPickUpAction(Player* player, Map* map)
	: mPlayer(player), mMap(map)
{
	mTarget = mPlayer->Target();
	Invoke(new MoveCommand(mPlayer, mMap));
}

void WalkToPickUpAction::Update()
{
	if (mPlayer->CurrentPath().empty())
	{
		mPlayer->Target(mTarget);
		Invoke(new PickUpCommand(mPlayer, mMap));
		mComplete = true;
	}
}