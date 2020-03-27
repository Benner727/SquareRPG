#pragma once

#include <Square.h>

#include "Game/Player/Inventory.h"
#include "Game/Interface/ActionsMenu.h"

class InventoryInterface : public Square::GameObject
{
private:
	Inventory& mInventory;

	Square::Sprite* mBackground;

	ActionsMenu* mActionsMenu;

	std::string mCurrentAction;
	int mSelectedSlot;

	Uint32 mLastClick;
	Square::Vector2 mLastPos;
	int mDragSlot;

	int PosToSlot(Square::Vector2 pos);
	std::string GetAction();

public:
	InventoryInterface(Inventory& inventory);
	~InventoryInterface();

	bool ContainsClick() const;

	Item* GetSlot(Square::Vector2 pos);

	inline bool MenuOpened() const { return (mActionsMenu != nullptr); }
	inline std::string CurrentAction() const { return mCurrentAction; }

	void Update();
	void Render();
};