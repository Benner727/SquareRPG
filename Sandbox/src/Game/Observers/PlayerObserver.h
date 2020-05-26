#pragma once

#include "Game/Observers/IObserver.h"
#include "Game/Interface/PlayerInterface.h"
#include "Game/Commands/KillPlayerCommand.h"

class PlayerObserver : public IObserver<Player>
{
private:
	std::shared_ptr<PlayerInterface> mPlayerInterface;
	std::shared_ptr<Map> mMap;
	std::shared_ptr<MessageLog> mMessageLog;

	void Invoke(ICommand* command)
	{
		if (command->CanExecute())
			command->Execute();
	}

public:
	PlayerObserver(std::shared_ptr<PlayerInterface> playerInterface, std::shared_ptr<Map> map, std::shared_ptr<MessageLog> messageLog)
	{
		mPlayerInterface = playerInterface;
		mMap = map;
		mMessageLog = messageLog;
	}

	inline void Update(Player* player) override
	{
		mPlayerInterface.reset();
		std::shared_ptr<Player> p(player);
		Invoke(new KillPlayerCommand(p, mMap, mMessageLog));
	}
};