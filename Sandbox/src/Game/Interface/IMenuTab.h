#pragma once

#include <Square.h>

#include "Game/Interface/ActionsMenu.h"
#include "Game/Interface/Tooltip.h"

class IMenuTab : public Square::GameObject
{
private:
	Square::Sprite* mBackground;

	bool mCanDrag;
	bool mHasHover;

	void HandleLeftClick();
	void HandleMenus();

protected:
	ActionsMenu* mActionsMenu;
	Tooltip* mTooltip;

	SDL_Color mActiveColor;

	std::vector<Square::Vector2> mSlotPos;
	int mItemSize;

	std::string mCurrentAction;
	int mSelectedSlot;
	int mLastSlot;

	Uint32 mLastClick;
	Square::Vector2 mLastPos;
	int mDragSlot;

	float mHoverTimer;

	int PosToSlot(Square::Vector2 pos);
	virtual std::string GetAction() = 0;

	virtual void CreateActionMenu();
	virtual void CreateTooltip();

	virtual void SetActiveSlot(int slot) = 0;
	virtual bool IsActiveSlot(int slot) = 0;
	virtual void Swap(int slotOne, int slotTwo) = 0;
	virtual Square::GameObject* GetSlot(int slot) = 0;

public:
	IMenuTab(std::string backgroundPath, int itemSize, bool canDrag = false, bool hasHover = false);
	virtual ~IMenuTab();

	bool ContainsClick() const;
	
	virtual Square::GameObject* GetSlot(Square::Vector2 pos) = 0;

	inline bool MenuOpened() const { return (mActionsMenu != nullptr); }
	inline std::string CurrentAction() const { return mCurrentAction; }

	virtual void Update();
	virtual void Render();
};