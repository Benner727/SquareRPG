#pragma once

#include "Game/Observers/IObserver.h"
#include "Game/Interface/MessageLog.h"
#include "Game/World/Player/Skill.h"

class SkillObserver : public IObserver<Skill>
{
private:
	std::shared_ptr<MessageLog> mMessageLog;

public:
	SkillObserver(std::shared_ptr<MessageLog> messageLog)
	{
		mMessageLog = messageLog;
	}

	inline void Update(Skill* skill) override
	{
		std::string message = "Congratulations, your " + skill->SkillName() + " is now level " + std::to_string(skill->Level()) + "!";
		mMessageLog->AddMessage(message, { 0, 0, 0, 255 });
	}
};