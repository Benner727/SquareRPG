#include "InventoryInterface.h"

InventoryInterface::InventoryInterface(Inventory& inventory)
	: mInventory(inventory)
{
	mBackground = new Square::Sprite("Graphics/panel_brown.png");
	mBackground->Parent(this);
	mBackground->Pos(mBackground->ScaledDimensions() * 0.5f);

	mActionsMenu = nullptr;

	mLastClick = 0;
	mDragSlot = -1;
}

InventoryInterface::~InventoryInterface()
{
	delete mBackground;
	delete mActionsMenu;
}

int InventoryInterface::PosToSlot(Square::Vector2 pos)
{
	int x = (pos.x - Pos().x) / 48;;
	int y = (pos.y - Pos().y) / 48;;

	int slot = x + y * 4;

	if (slot < 0 || slot > Inventory::INVENTORY_SIZE)
		slot = -1;

	return slot;
}

Item* InventoryInterface::GetSlot(Square::Vector2 pos)
{
	int slot = PosToSlot(pos);

	if (slot != mInventory.ActiveSlot())
	{
		if (Item* item = mInventory.GetItem(slot))
		{
			if (pos.x >= item->Pos().x - 16.0f &&
				pos.x <= item->Pos().x + 16.0f &&
				pos.y >= item->Pos().y - 16.0f &&
				pos.y <= item->Pos().y + 16.0f)
			{
				return item;
			}
		}
	}
	
	return nullptr;
}

std::string InventoryInterface::GetAction()
{
	std::string action = "";

	Square::Vector2 pos = Square::InputHandler::Instance().MousePos();

	if (Item* item = GetSlot(pos))
	{
		action = item->InventoryActions().front();
	}

	return action;
}


bool InventoryInterface::ContainsClick() const
{
	Square::Vector2 pos = Square::InputHandler::Instance().MousePos();

	if (pos.x >= mBackground->Pos().x - mBackground->ScaledDimensions().x * 0.5f &&
		pos.x <= mBackground->Pos().x + mBackground->ScaledDimensions().x * 0.5f &&
		pos.y >= mBackground->Pos().y - mBackground->ScaledDimensions().y * 0.5f &&
		pos.y <= mBackground->Pos().y + mBackground->ScaledDimensions().y * 0.5f)
		return true;

	return false;
}

void InventoryInterface::Update()
{
	mCurrentAction.clear();

	if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::right) && mDragSlot == -1)
	{
		if (Active())
		{
			if (Item* item = GetSlot(Square::InputHandler::Instance().MousePos()))
			{
				mActionsMenu = new ActionsMenu(item->Name(), item->InventoryActions(), Square::InputHandler::Instance().MousePos());
				mSelectedSlot = PosToSlot(Square::InputHandler::Instance().MousePos());
			}
		}
	}

	if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::left))
	{
		if (mActionsMenu)
		{
			mCurrentAction = mActionsMenu->Action();
			mInventory.ActiveSlot(mSelectedSlot);
			mSelectedSlot = -1;
			mActionsMenu->Active(false);
		}
		else if (ContainsClick() && Active())
		{
			mLastClick = SDL_GetTicks();
			mLastPos = Square::InputHandler::Instance().MousePos();
			mSelectedSlot = PosToSlot(mLastPos);
		}
	}
	else if (Square::InputHandler::Instance().MouseButtonReleased(Square::InputHandler::left) && mLastClick != 0)
	{
		mLastClick = 0;

		if (SDL_GetTicks() - mLastClick < 100 || mDragSlot == -1)
		{
			mCurrentAction = GetAction();
			mInventory.ActiveSlot(mSelectedSlot);
			mSelectedSlot = -1;
		}

		if (mDragSlot != -1)
		{
			int swapToSlot = PosToSlot(Square::InputHandler::Instance().MousePos());

			if (swapToSlot != -1)
				mInventory.Swap(mDragSlot, swapToSlot);

			mDragSlot = -1;
		}
	}
	else
	{
		if (mLastClick != 0)
		{
			if (!(mLastPos == Square::InputHandler::Instance().MousePos()))
			{
				mDragSlot = PosToSlot(mLastPos);
			}
		}
	}

	if (mActionsMenu)
	{
		mActionsMenu->Update();

		if (!mActionsMenu->Active())
		{
			delete mActionsMenu;
			mActionsMenu = nullptr;
		}
	}
}

void InventoryInterface::Render()
{
	mBackground->Render();

	int slot = 0;
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			if (Item* item = mInventory.GetItem(slot))
			{
				if (mDragSlot == slot)
				{
					item->Parent(nullptr);
					item->Pos(Square::InputHandler::Instance().MousePos());
				}
				else
				{
					item->Parent(this);
					item->Pos(Square::Vector2(x * 48.0f + 32.0f, y * 48.0f + 32.0f));
				}

				item->Render();
			}

			slot++;
		}
	}

	if (mActionsMenu)
		mActionsMenu->Render();
}