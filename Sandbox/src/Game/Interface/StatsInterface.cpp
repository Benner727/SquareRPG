#include "StatsInterface.h"

StatsInterface::StatsInterface(Skills& skills)
	: IMenuTab("Graphics/panel_brown.png", { 16, 16 }, false, true), mSkills(skills)
{
	for (int x = 0; x < 3; x++)
	{
		for (int y = 0; y < 7; y++)
		{
			mSlotPos.push_back(Square::Vector2(x * 64.0f + 32.0f, y * 32.0f + 32.0f));
		}
	}

	mExperience = 0;
}

std::string StatsInterface::GetAction()
{
	std::string action = "";

	Square::Vector2 pos = Square::InputHandler::Instance().MousePos();

	if (Skill* skill = dynamic_cast<Skill*>(GetSlot(pos).get()))
	{
		action = "";
	}

	return action;
}

void StatsInterface::CreateActionMenu()
{

}

void StatsInterface::CreateTooltip()
{
	if (Skill* skill = dynamic_cast<Skill*>(GetSlot(Square::InputHandler::Instance().MousePos()).get()))
	{
		mSelectedSlot = PosToSlot(Square::InputHandler::Instance().MousePos());

		if ((!mTooltip || mExperience != skill->Experience()) && mHoverTimer > 0.5f)
		{
			mExperience = skill->Experience();
			delete mTooltip;
			mTooltip = new Tooltip({ skill->SkillName() + " EXP:" + std::to_string(mExperience) }, skill->Pos() + 16.0f);
		}
	}
	else
		mSelectedSlot = -1;
}

std::shared_ptr<Square::GameObject> StatsInterface::GetSlot(int slot, bool includeActive)
{
	std::shared_ptr<Skill> skill = nullptr;

	if (slot >= 0 && slot < mSkills.GetSkills().size())
	{
		skill = mSkills.GetSkills()[slot];
	}

	return skill;
}

std::shared_ptr<Square::GameObject> StatsInterface::GetSlot(Square::Vector2 pos, bool includeActive)
{
	int slot = PosToSlot(pos);

	return GetSlot(slot, includeActive);
}