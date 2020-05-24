#pragma once

#include "Game/Interface/IMenuTab.h"
#include "Game/World/Player/Prayer/IPrayerBook.h"

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
	std::shared_ptr<Square::GameObject> GetSlot(int slot, bool includeActive = true);

public:
	PrayerInterface(IPrayerBook& prayerBook);
	~PrayerInterface() = default;

	std::shared_ptr<Square::GameObject> GetSlot(Square::Vector2 pos, bool includeActive = true);
};