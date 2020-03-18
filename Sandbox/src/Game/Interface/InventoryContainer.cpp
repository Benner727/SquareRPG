#include "InventoryContainer.h"

#include "MenuContainer.h"

InventoryContainer::InventoryContainer(Inventory& inventory) :
	mInventory(inventory), mDrag(false), mLastClick(-1)
{
	mWidth = CONTAINER_WIDTH;
	mHeight = CONTAINER_HEIGHT;
	mPosition = Square::Vector2(
		Square::Graphics::SCREEN_WIDTH - CONTAINER_WIDTH / 2 - PADDING,
		Square::Graphics::SCREEN_HEIGHT - CONTAINER_HEIGHT / 2 - MenuContainer::MENU_HEIGHT - PADDING * 2);

	mContainer = Square::Sprite(CONTAINER_PATH);
	mContainer.Pos(mPosition);

	mButtonSelected = Square::Sprite(BUTTON_SELECTED);
	mButtonUnselected = Square::Sprite(BUTTON_UNSELECTED);
	mButtonSelected.Parent(&mContainer);
	mButtonUnselected.Parent(&mContainer);

	mTooltip = nullptr;
}

InventoryContainer::~InventoryContainer()
{
	delete mTooltip;
}

int InventoryContainer::SlotIndex(Square::Vector2 position)
{
	int row = (position.x - (Square::Graphics::SCREEN_WIDTH - CONTAINER_WIDTH)) / BUTTON_WIDTH;
	int col = (position.y - (Square::Graphics::SCREEN_HEIGHT - CONTAINER_HEIGHT - MenuContainer::MENU_HEIGHT)) / BUTTON_HEIGHT;
	int slotIndex = row + col * 4;
	return slotIndex;
}

void InventoryContainer::LeftClick(Square::Vector2 position)
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
		int slotIndex = SlotIndex(position);
		Item* mItem = mInventory.GetItem(slotIndex);
		if (mItem)
		{
			std::vector<std::string> actions = mItem->InventoryActions();
			mTooltip = new Tooltip(mItem->Name(), actions);
			mTooltip->Position(position);
		}
	}
}

void InventoryContainer::Drag(Square::Vector2 position)
{
	if (mInputHandler.MouseButtonPressed(Square::InputHandler::MOUSE_BUTTON::left))
	{
		mLastClick = std::clock();
	}
	else if (mInputHandler.MouseButtonReleased(Square::InputHandler::MOUSE_BUTTON::left))
	{
		int swapIndex = SlotIndex(position);
		mInventory.Swap(mInventory.ActiveSlot(), swapIndex);

		mDragPosition = Square::Vector2(-1, -1);
		mInventory.ActiveSlot(-1);

		mLastClick = -1;
		mDrag = false;
	}
	else if (mDrag)
	{
		mDragPosition = position;
	}
	else if (mLastClick != -1 && std::clock() - mLastClick > 100)
	{
		mDrag = true;
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

	if (!mTooltip && MouseIsOver(position))
	{
		Hover(position);
		LeftClick(position);
		RightClick(position);
		Drag(position);
	}
	else
	{
		mDragPosition = Square::Vector2(-1, -1);
		mInventory.ActiveSlot(-1);
		mActiveSlot = -1;
	}

	if (mTooltip)
	{
		if (!mTooltip->MouseOver(position) && mInputHandler.MouseButtonPressed(Square::InputHandler::left))
		{
			delete mTooltip;
			mTooltip = nullptr;
			return;
		}
	
		else if (mTooltip->Command() != "")
		{
			std::cout << mTooltip->Command() << std::endl; // get command of clicked button here
		}

		mTooltip->Update();
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

	if (mTooltip) mTooltip->Render();
}
