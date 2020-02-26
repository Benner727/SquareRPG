#pragma once

#include <vector>

#include "Game/Player/Prayer/Aura.h"

class IPrayerBook
{
protected:
	std::vector<Aura> mAuras;

public:
	virtual ~IPrayerBook() = default;

	virtual void Toggle(int index, int prayerLevel);
	void ToggleAllOff();

	bool Activated(int index) const;
	float PrayerDrain() const;

	inline std::vector<Aura> PrayerAuras() const { return mAuras; }
};