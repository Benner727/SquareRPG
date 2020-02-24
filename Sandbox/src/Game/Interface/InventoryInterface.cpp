#include "InventoryInterface.h"

#include "Menu.h"

InventoryInterface::InventoryInterface(Inventory* inventory) :
	mPosition(Square::Vector2(
		Square::Graphics::SCREEN_WIDTH - CONTAINER_WIDTH / 2,
		Square::Graphics::SCREEN_HEIGHT - CONTAINER_HEIGHT / 2 - Menu::MENU_HEIGHT)),
	mContainer(Square::Sprite(CONTAINER_PATH, 0, 0, CONTAINER_WIDTH, CONTAINER_HEIGHT)),
	mButtonSelected(Square::Sprite(BUTTON_UNSELECTED, 0, 0, BUTTON_WIDTH, BUTTON_HEIGHT)),
	mButtonUnselected(Square::Sprite(BUTTON_SELECTED, 0, 0, BUTTON_WIDTH, BUTTON_HEIGHT)),
	mInventory(inventory)
{
	mContainer.Pos(mPosition);
	mButtonSelected.Parent(&mContainer);
	mButtonUnselected.Parent(&mContainer);
}

InventoryInterface::~InventoryInterface()
{
}

bool InventoryInterface::MouseIsOver(Square::Vector2 position)
{
	return (
		position.x >= mPosition.x - CONTAINER_WIDTH / 2 &&
		position.x <= mPosition.x + CONTAINER_WIDTH / 2 &&
		position.y >= mPosition.y - CONTAINER_HEIGHT / 2 &&
		position.y <= mPosition.y + CONTAINER_HEIGHT / 2
	);
}

void InventoryInterface::HandleClick(Square::Vector2 position)
{
	int row = (position.x - (Square::Graphics::SCREEN_WIDTH - CONTAINER_WIDTH)) / BUTTON_WIDTH;
	int col = (position.y - (Square::Graphics::SCREEN_HEIGHT - CONTAINER_HEIGHT - Menu::MENU_HEIGHT)) / BUTTON_HEIGHT;
	int slotIndex = row + col * 4;

	mInventory->ActiveSlot(slotIndex);
}

void InventoryInterface::Render()
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

		if (mInventory->ActiveSlot() == slot)
		{
			mButtonSelected.Pos(position);
			mButtonSelected.Render();
		}
		else
		{
			mButtonUnselected.Pos(position);
			mButtonUnselected.Render();
		}

		Item* item = mInventory->GetItem(slot);
		if (item)
		{
			item->Render();
		}

		row += 1;
	}
}
