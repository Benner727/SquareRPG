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

void InventoryContainer::LeftClick(Square::Vector2 position)
{
	int row = (position.x - (Square::Graphics::SCREEN_WIDTH - CONTAINER_WIDTH)) / BUTTON_WIDTH;
	int col = (position.y - (Square::Graphics::SCREEN_HEIGHT - CONTAINER_HEIGHT - MenuContainer::MENU_HEIGHT)) / BUTTON_HEIGHT;
	int slotIndex = row + col * 4;

	Item* mItem = mInventory.GetItem(slotIndex);
	if (mItem)
	{
		mInventory.ActiveSlot(slotIndex);
	}
}

void InventoryContainer::RightClick(Square::Vector2 position)
{
}

void InventoryContainer::Drag(Square::Vector2 position)
{
}

void InventoryContainer::Hover(Square::Vector2 position)
{
}

void InventoryContainer::Update()
{
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

		if (mInventory.ActiveSlot() == slot)
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
			item->Parent(&mContainer);
			item->Pos(position);
			item->Render();
		}

		row += 1;
	}
}
