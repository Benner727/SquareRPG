#pragma once

#include <vector>

#include "Game/World/Player/Prayer/Aura.h"

class IPrayerBook
{
protected:
	std::vector<std::shared_ptr<Aura>> mAuras;

	int mActiveSlot = -1;

public:
	virtual ~IPrayerBook() = default;

	virtual void ActiveSlot(int slot) { mActiveSlot = slot; }
	virtual int ActiveSlot() const { return mActiveSlot; }

	virtual void Toggle(int index);
	void ToggleAllOff();

	bool Activated(int index) const;
	float PrayerDrain() const;

	inline std::vector<std::shared_ptr<Aura>> PrayerAuras() const { return mAuras; }
};