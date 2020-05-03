#pragma once

#include <vector>

#include "Game/Player/Prayer/Aura.h"

class IPrayerBook
{
protected:
	std::vector<Aura*> mAuras;

	int mActiveSlot = -1;

public:
	virtual ~IPrayerBook()
	{
		for (auto& aura : mAuras)
			delete aura;
	}

	virtual void ActiveSlot(int slot) { mActiveSlot = slot; }
	virtual int ActiveSlot() const { return mActiveSlot; }

	virtual void Toggle(int index);
	void ToggleAllOff();

	bool Activated(int index) const;
	float PrayerDrain() const;

	inline std::vector<Aura*> PrayerAuras() const { return mAuras; }
};