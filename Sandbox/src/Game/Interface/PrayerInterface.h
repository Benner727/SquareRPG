#pragma once

#include "Game/Player/Prayer/IPrayerBook.h"
#include "Game/Interface/ActionsMenu.h"
#include "Game/Interface/Tooltip.h"

class PrayerInterface : public Square::GameObject
{
private:
	IPrayerBook& mPrayerBook;

	Square::Sprite* mBackground;

	ActionsMenu* mActionsMenu;
	Tooltip* mTooltip;

	std::string mCurrentAction;
	int mSelectedSlot;

	float mHoverTimer;

	int PosToSlot(Square::Vector2 pos);
	std::string GetAction();

public:
	PrayerInterface(IPrayerBook& prayerBook);
	~PrayerInterface();

	bool ContainsClick() const;

	Aura* GetSlot(Square::Vector2 pos);

	inline bool MenuOpened() const { return (mActionsMenu != nullptr); }
	inline std::string CurrentAction() const { return mCurrentAction; }

	void Update();
	void Render();
};