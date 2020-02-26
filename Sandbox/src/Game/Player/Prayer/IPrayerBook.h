#pragma once

#include <vector>

#include "Game/Player/Prayer/Aura.h"

class IPrayerBook
{
protected:
	std::vector<Aura*> mAuras;

public:
	virtual ~IPrayerBook()
	{
		for (auto& aura : mAuras)
			delete aura;
	}

	virtual void Toggle(int index, int prayerLevel);
	void ToggleAllOff();

	bool Activated(int index) const;
	float PrayerDrain() const;

	inline const std::vector<const Aura*> &PrayerAuras() const { return *reinterpret_cast<const std::vector<const Aura*>*>(&mAuras); }
};