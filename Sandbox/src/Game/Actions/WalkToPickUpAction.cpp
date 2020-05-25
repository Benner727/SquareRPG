#include "WalkToPickUpAction.h"

#include "Game/Commands/MoveCommand.h"
#include "Game/Commands/PickUpCommand.h"

WalkToPickUpAction::WalkToPickUpAction(std::shared_ptr<Player> player, std::shared_ptr<Map> map, std::shared_ptr<MessageLog> messageLog)
	: mPlayer(player), mMap(map), mMessageLog(messageLog)
{
	mTarget = mPlayer->Target();
	Invoke(new MoveCommand(mPlayer, mMap));
}

void WalkToPickUpAction::Update()
{
	if (mPlayer->CurrentPath().empty())
	{
		mPlayer->Target(mTarget);
		Invoke(new PickUpCommand(mPlayer, mMap, mMessageLog));
		mComplete = true;
	}
}