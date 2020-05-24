#include "IPrayerBook.h"

void IPrayerBook::Toggle(int index)
{
	if (!mAuras[index]->Activated())
	{
		if (mAuras[index]->AuraType() == AuraType::combat)
		{
			for (auto& aura : mAuras)
			{
				if (aura->AuraType() != AuraType::over_head)
					aura->Activated(false);
			}
		}
		else if (mAuras[index]->AuraType() == AuraType::over_head)
		{
			for (auto& aura : mAuras)
			{
				if (aura->AuraType() == AuraType::over_head)
					aura->Activated(false);
			}
		}
		else if (mAuras[index]->AuraType() != AuraType::utility)
		{
			for (auto& aura : mAuras)
			{
				if (aura->AuraType() == mAuras[index]->AuraType() || aura->AuraType() == AuraType::combat)
					aura->Activated(false);
			}
		}
	}
	
	mAuras[index]->Activated(!mAuras[index]->Activated());
}

void IPrayerBook::ToggleAllOff()
{
	for (auto& aura : mAuras)
	{
		aura->Activated(false);
	}
}

bool IPrayerBook::Activated(int index) const
{
	return mAuras[index]->Activated();
}

float IPrayerBook::PrayerDrain() const
{
	float drainRate = 0.0f;

	for (const auto& aura : mAuras)
	{
		if (aura->Activated())
			drainRate += aura->DrainRate();
	}

	if (drainRate > 0.0f)
		drainRate = 1.0f / drainRate;

	return drainRate;
}