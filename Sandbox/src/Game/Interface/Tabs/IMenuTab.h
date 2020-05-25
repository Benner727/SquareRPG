#pragma once

#include <Square.h>

#include "Game/Interface/Tools/ActionsMenu.h"
#include "Game/Interface/Tools/Tooltip.h"

class IMenuTab : public Square::GameObject
{
private:
	Square::Sprite* mBackground;

	bool mInUse;

	bool mCanDrag;
	bool mHasHover;

	void HandleLeftClick();
	void HandleMenus();

protected:
	ActionsMenu* mActionsMenu;
	Tooltip* mTooltip;

	SDL_Color mActiveColor;

	std::vector<Square::Sprite*> mIcons;
	std::vector<Square::Vector2> mSlotPos;
	Square::Vector2 mItemSize;

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
	virtual std::shared_ptr<Square::GameObject> GetSlot(int slot, bool includeActive = true) = 0;

	virtual void PrivateUpdate() {}
	virtual void PrivateRender() {}

public:
	IMenuTab(std::string backgroundPath, Square::Vector2 itemSize, bool canDrag = false, bool hasHover = false);
	virtual ~IMenuTab();

	inline bool InUse() const { return mInUse; }
	inline void InUse(bool inUse) { mInUse = inUse; }

	bool ContainsClick() const;
	
	virtual std::shared_ptr<Square::GameObject> GetSlot(Square::Vector2 pos, bool includeActive = true) = 0;

	inline bool MenuOpened() const { return (mActionsMenu != nullptr); }
	inline std::string CurrentAction() const { return mCurrentAction; }

	virtual void Update();
	virtual void Render();
};