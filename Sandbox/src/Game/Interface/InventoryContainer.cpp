#include "InventoryContainer.h"

#include "MenuContainer.h"

InventoryContainer::InventoryContainer(Inventory& inventory) :
	mInventory(inventory)
{
	mWidth = CONTAINER_WIDTH;
	mHeight = CONTAINER_HEIGHT;
	mPosition = Square::Vector2(
		Square::Graphics::SCREEN_WIDTH - CONTAINER_WIDTH / 2,
		Square::Graphics::SCREEN_HEIGHT - CONTAINER_HEIGHT / 2 - MenuContainer::MENU_HEIGHT);

	mContainer = Square::Sprite(CONTAINER_PATH);
	mContainer.Pos(mPosition);

	mButtonSelected = Square::Sprite(BUTTON_UNSELECTED);	
	mButtonUnselected = Square::Sprite(BUTTON_SELECTED);
	mButtonSelected.Parent(&mContainer);
	mButtonUnselected.Parent(&mContainer);
}

InventoryContainer::~InventoryContainer()
{
}

int InventoryContainer::SlotIndex(Square::Vector2 position)
{
	int row = (position.x - (Square::Graphics::SCREEN_WIDTH - CONTAINER_WIDTH)) / BUTTON_WIDTH;
	int col = (position.y - (Square::Graphics::SCREEN_HEIGHT - CONTAINER_HEIGHT - MenuContainer::MENU_HEIGHT)) / BUTTON_HEIGHT;
	int slotIndex = row + col * 4;
	return slotIndex;
}

void InventoryContainer::LeftClick(Square::Vector2 position) // THE ITEM DRAGS TO YOU (100ms) -- record timer when you click and record the release
{
	if (mInputHandler.MouseButtonPressed(Square::InputHandler::MOUSE_BUTTON::left))
	{
		int slotIndex = SlotIndex(position);
		Item* mItem = mInventory.GetItem(slotIndex);
		if (mItem)
		{
			mInventory.ActiveSlot(slotIndex);
		}
		else
		{
			mInventory.ActiveSlot(-1);
		}
	}
}

void InventoryContainer::RightClick(Square::Vector2 position)
{
	if (mInputHandler.MouseButtonPressed(Square::InputHandler::MOUSE_BUTTON::right))
	{

	}
}

void InventoryContainer::Drag(Square::Vector2 position)
{
	if (mInputHandler.MouseButtonDown(Square::InputHandler::MOUSE_BUTTON::left))
	{
		mDragPosition = position;
	}
	else if (mInputHandler.MouseButtonReleased(Square::InputHandler::MOUSE_BUTTON::left))
	{
		int swapIndex = SlotIndex(position);
		mInventory.Swap(mInventory.ActiveSlot(), swapIndex);

		mDragPosition = Square::Vector2(-1, -1);
		mInventory.ActiveSlot(-1);
	}
}

void InventoryContainer::Hover(Square::Vector2 position)
{
	int slotIndex = SlotIndex(position);
	mActiveSlot = slotIndex;
}

void InventoryContainer::Update()
{
	Square::Vector2 position = mInputHandler.MousePos();

	if (MouseIsOver(position))
	{
		Hover(position);
		LeftClick(position);
		Drag(position);
	}
	else
	{
		mDragPosition = Square::Vector2(-1, -1);
		mInventory.ActiveSlot(-1);
		mActiveSlot = -1;
	}

}

void InventoryContainer::Render()
{
	mContainer.Render();

	int row = 0;
	int col = 0;

	for (int slot = 0; slot < Inventory::INVENTORY_SIZE; slot++)
	{
		if (slot / 4 != col)
		{
			row = 0;
			col = slot / 4;
		}

		Square::Vector2 position = Square::Vector2(
			(BUTTON_WIDTH-CONTAINER_WIDTH)/2 + (row*BUTTON_WIDTH),
			(BUTTON_HEIGHT-CONTAINER_HEIGHT)/2 + (col*BUTTON_HEIGHT));

		if (mActiveSlot == slot || mInventory.ActiveSlot() == slot)
		{
			mButtonSelected.Pos(position);
			mButtonSelected.Render();
		}
		else
		{
			mButtonUnselected.Pos(position);
			mButtonUnselected.Render();
		}

		Item* item = mInventory.GetItem(slot);
		if (item)
		{
			if (mInventory.ActiveSlot() == slot && mDragPosition.x != -1 && mDragPosition.y != -1)
			{
				item->Parent(nullptr);
				item->Pos(mDragPosition);
			}
			else
			{
				item->Parent(&mContainer);
				item->Pos(position);
			}

			item->Render();
		}

		row += 1;
	}
}
