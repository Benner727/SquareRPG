#include "CombatInterface.h"

CombatInterface::CombatInterface(Player& player)
	: IMenuTab("Graphics/panel_brown.png", { 75, 40 }, false, false), mPlayer(player)
{
	mSlotPos.push_back({ 60, 85 });
	mSlotPos.push_back({ 150, 85 });
	mSlotPos.push_back({ 60, 160 });
	mSlotPos.push_back({ 150, 160 });

	mCurrentCombatStyle = CombatStyle::none;
	PrivateUpdate();
}


std::string CombatInterface::GetAction()
{
	std::string action = "";

	Square::Vector2 pos = Square::InputHandler::Instance().MousePos();

	if (CombatButton* button = dynamic_cast<CombatButton*>(GetSlot(pos).get()))
	{
		action = "Set Combat Stance";
	}

	return action;
}

void CombatInterface::CreateActionMenu()
{

}

void CombatInterface::CreateTooltip()
{

}

inline void CombatInterface::SetActiveSlot(int slot)
{
	if (slot != -1)
	{
		for (int i = 0; i < mCombatButtons.size(); i++)
			mCombatButtons[i]->Selected(false);

		mCombatButtons[slot]->Selected(true);
		mPlayer.GetCombatStance().Set(mCombatButtons[slot]->GetCombatOption());
	}
}

inline bool CombatInterface::IsActiveSlot(int slot)
{
	if (slot != -1 && slot < mCombatButtons.size())
	{
		return mCombatButtons[slot]->Selected();
	}

	return false;
}

std::shared_ptr<Square::GameObject> CombatInterface::GetSlot(int slot, bool includeActive)
{
	std::shared_ptr<CombatButton> button = nullptr;

	if (slot != -1 && slot < mCombatButtons.size())
	{
		button = mCombatButtons[slot];
	}

	return button;
}

void CombatInterface::MeleeSetup()
{
	mCombatButtons.clear();
	mCombatButtons.push_back(std::make_shared<CombatButton>("Accurate", CombatOption::melee_accurate));
	mCombatButtons.push_back(std::make_shared<CombatButton>("Aggressive", CombatOption::melee_aggressive));
	mCombatButtons.push_back(std::make_shared<CombatButton>("Controlled", CombatOption::melee_controlled));
	mCombatButtons.push_back(std::make_shared<CombatButton>("Defensive", CombatOption::melee_defensive));

	for (auto& button : mCombatButtons)
	{
		if (button->GetCombatOption() == mPlayer.GetCombatStance().Get())
			button->Selected(true);
	}
}

void CombatInterface::RangedSetup()
{
	mCombatButtons.clear();
	mCombatButtons.push_back(std::make_shared<CombatButton>("Accurate", CombatOption::ranged_accurate));
	mCombatButtons.push_back(std::make_shared<CombatButton>("Rapid", CombatOption::ranged_rapid));
	mCombatButtons.push_back(std::make_shared<CombatButton>("Longrange", CombatOption::ranged_longrange));

	for (auto& button : mCombatButtons)
	{
		if (button->GetCombatOption() == mPlayer.GetCombatStance().Get())
			button->Selected(true);
	}
}

void CombatInterface::MagicSetup()
{
	mCombatButtons.clear();
	mCombatButtons.push_back(std::make_shared<CombatButton>("Standard", CombatOption::magic_standard));
	mCombatButtons.push_back(std::make_shared<CombatButton>("Defensive", CombatOption::magic_defensive));

	for (auto& button : mCombatButtons)
	{
		if (button->GetCombatOption() == mPlayer.GetCombatStance().Get())
			button->Selected(true);
	}
}

void CombatInterface::PrivateUpdate()
{
	if (mCurrentCombatStyle != mPlayer.GetCombatStance().GetCombatStyle())
	{
		mCurrentCombatStyle = mPlayer.GetCombatStance().GetCombatStyle();

		switch (mCurrentCombatStyle)
		{
		case CombatStyle::melee:
			MeleeSetup();
			break;
		case CombatStyle::ranged:
			RangedSetup();
			break;
		case CombatStyle::magic:
			MagicSetup();
			break;
		default:
			MeleeSetup();
		}
	}
}

std::shared_ptr<Square::GameObject> CombatInterface::GetSlot(Square::Vector2 pos, bool includeActive)
{
	int slot = PosToSlot(pos);

	return GetSlot(slot, includeActive);
}
