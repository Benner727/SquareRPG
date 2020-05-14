#include "PrayerInterface.h"

PrayerInterface::PrayerInterface(IPrayerBook& prayerBook)
	: IMenuTab("Graphics/panel_brown.png", 32, false, true), mPrayerBook(prayerBook)
{
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			mSlotPos.push_back(Square::Vector2(x * 48.0f + 32.0f, y * 48.0f + 32.0f));
		}
	}
}

std::string PrayerInterface::GetAction()
{
	std::string action = "";

	Square::Vector2 pos = Square::InputHandler::Instance().MousePos();

	if (Aura* aura = dynamic_cast<Aura*>(GetSlot(pos).get()))
	{
		action = aura->Activated() ? "Deactivate" : "Activate";
	}

	return action;
}

void PrayerInterface::CreateActionMenu()
{
	if (Aura* aura = dynamic_cast<Aura*>(GetSlot(Square::InputHandler::Instance().MousePos()).get()))
	{
		std::string action = aura->Activated() ? "Deactivate" : "Activate";
		mActionsMenu = new ActionsMenu(aura->Name(), { action }, Square::InputHandler::Instance().MousePos());
		mSelectedSlot = PosToSlot(Square::InputHandler::Instance().MousePos());

		delete mTooltip;
		mTooltip = nullptr;
	}
}

void PrayerInterface::CreateTooltip()
{
	if (Aura* aura = dynamic_cast<Aura*>(GetSlot(Square::InputHandler::Instance().MousePos()).get()))
	{
		mSelectedSlot = PosToSlot(Square::InputHandler::Instance().MousePos());

		if (!mTooltip && mHoverTimer > 0.5f)
			mTooltip = new Tooltip({ "Level " + std::to_string(aura->LevelReq()), aura->Name() }, aura->Pos() + 16.0f);
	}
	else
		mSelectedSlot = -1;
}

std::shared_ptr<Square::GameObject> PrayerInterface::GetSlot(int slot, bool includeActive)
{
	std::shared_ptr<Aura> aura = nullptr;

	if (slot >= 0 && slot < mPrayerBook.PrayerAuras().size())
	{
		if (includeActive || (slot != mPrayerBook.ActiveSlot() && !includeActive))
			aura = mPrayerBook.PrayerAuras()[slot];
	}

	return aura;
}

std::shared_ptr<Square::GameObject> PrayerInterface::GetSlot(Square::Vector2 pos, bool includeActive)
{
	int slot = PosToSlot(pos);

	return GetSlot(slot, includeActive);
}