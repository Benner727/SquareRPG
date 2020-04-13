#pragma once

#include "Game/Interface/IMenuTab.h"
#include "Game/Player/Prayer/IPrayerBook.h"

class PrayerInterface : public IMenuTab
{
private:
	IPrayerBook& mPrayerBook;

	std::string GetAction();

	void CreateActionMenu();
	void CreateTooltip();

	inline void SetActiveSlot(int slot) { mPrayerBook.ActiveSlot(slot); }
	inline bool IsActiveSlot(int slot) { return mPrayerBook.PrayerAuras()[slot]->Activated(); }
	inline void Swap(int slotOne, int slotTwo) {}
	Square::GameObject* GetSlot(int slot);

public:
	PrayerInterface(IPrayerBook& prayerBook);
	~PrayerInterface() = default;

	Square::GameObject* GetSlot(Square::Vector2 pos);
};