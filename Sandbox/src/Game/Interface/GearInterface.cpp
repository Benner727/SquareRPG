#include "GearInterface.h"

GearInterface::GearInterface(Gear& gear)
	: mGear(gear)
{
	mBackground = new Square::Sprite("Graphics/panel_brown.png");
	mBackground->Parent(this);
	mBackground->Pos(mBackground->ScaledDimensions() * 0.5f);

	mActionsMenu = nullptr;
}

GearInterface::~GearInterface()
{
	delete mBackground;
	delete mActionsMenu;
}

int GearInterface::PosToSlot(Square::Vector2 pos)
{
	int x = (pos.x - Pos().x) / 48.0f;
	int y = (pos.y - Pos().y) / 48.0f;

	int slot = x + y * 2;

	if (slot < 0 || slot > Gear::EquipmentSlot::TOTAL_SLOTS)
		slot = -1;

	return slot;
}

Item* GearInterface::GetSlot(Square::Vector2 pos)
{
	Item* item = mGear.GetItem(PosToSlot(pos));

	if (item)
	{
		if (pos.x >= item->Pos().x - 16.0f &&
			pos.x <= item->Pos().x + 16.0f &&
			pos.y >= item->Pos().y - 16.0f &&
			pos.y <= item->Pos().y + 16.0f)
		{
			return item;
		}
	}

	return nullptr;
}

std::string GearInterface::GetAction()
{
	std::string action = "";

	Square::Vector2 pos = Square::InputHandler::Instance().MousePos();

	if (Item* item = GetSlot(pos))
	{
		action = "Unequip";
	}

	return action;
}


bool GearInterface::ContainsClick() const
{
	Square::Vector2 pos = Square::InputHandler::Instance().MousePos();

	if (pos.x >= mBackground->Pos().x - mBackground->ScaledDimensions().x * 0.5f &&
		pos.x <= mBackground->Pos().x + mBackground->ScaledDimensions().x * 0.5f &&
		pos.y >= mBackground->Pos().y - mBackground->ScaledDimensions().y * 0.5f &&
		pos.y <= mBackground->Pos().y + mBackground->ScaledDimensions().y * 0.5f)
		return true;

	return false;
}

void GearInterface::Update()
{
	mCurrentAction.clear();

	if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::right))
	{
		if (Active())
		{
			if (Item* item = GetSlot(Square::InputHandler::Instance().MousePos()))
			{
				mActionsMenu = new ActionsMenu(item->Name(), { "Unequip" }, Square::InputHandler::Instance().MousePos());
				mSelectedSlot = PosToSlot(Square::InputHandler::Instance().MousePos());
			}
		}
	}

	if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::left))
	{
		if (mActionsMenu)
		{
			mCurrentAction = mActionsMenu->Action();
			if (!mCurrentAction.empty())
				mGear.ActiveSlot(mSelectedSlot);
			mSelectedSlot = -1;
			mActionsMenu->Active(false);
		}
		else if (ContainsClick() && Active())
		{
			mCurrentAction = GetAction();
			mSelectedSlot = PosToSlot(Square::InputHandler::Instance().MousePos());
			mGear.ActiveSlot(mSelectedSlot);
			mSelectedSlot = -1;
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

void GearInterface::Render()
{
	mBackground->Render();

	int slot = 0;
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 2; x++)
		{
			if (Item* item = mGear.GetItem(slot))
			{
				item->Parent(this);
				item->Pos(Square::Vector2(x * 48.0f + 32.0f, y * 48.0f + 32.0f));
				item->Render();
			}

			slot++;
		}
	}

	if (mActionsMenu)
		mActionsMenu->Render();
}