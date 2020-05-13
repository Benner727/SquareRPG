#include "IMenuTab.h"

IMenuTab::IMenuTab(std::string backgroundPath, int itemSize, bool canDrag, bool hasHover)
	: mItemSize(itemSize), mCanDrag (canDrag), mHasHover(hasHover)
{
	mBackground = new Square::Sprite(backgroundPath);
	mBackground->Parent(this);
	mBackground->Pos(mBackground->ScaledDimensions() * 0.5f);

	mInUse = false;

	mActionsMenu = nullptr;
	mTooltip = nullptr;

	mActiveColor = { 125, 25, 25, 255 };

	mCurrentAction = "";
	mSelectedSlot = -1;
	mLastSlot = -1;

	mLastClick = 0;
	mDragSlot = -1;

	mHoverTimer = 0.0f;
}

IMenuTab::~IMenuTab()
{
	delete mBackground;

	delete mActionsMenu;
	delete mTooltip;
}

int IMenuTab::PosToSlot(Square::Vector2 pos)
{
	int slot = -1;
	for (int i = 0; i < mSlotPos.size(); i++)
	{
		if (pos.x >= Pos().x + mSlotPos[i].x - mItemSize * 0.5f &&
			pos.x <= Pos().x + mSlotPos[i].x + mItemSize * 0.5f &&
			pos.y >= Pos().y + mSlotPos[i].y - mItemSize * 0.5f &&
			pos.y <= Pos().y + mSlotPos[i].y + mItemSize * 0.5f)
		{
			slot = i;
			break;
		}
	}

	return slot;
}

void IMenuTab::CreateActionMenu()
{
}

void IMenuTab::CreateTooltip()
{
}

bool IMenuTab::ContainsClick() const
{
	Square::Vector2 pos = Square::InputHandler::Instance().MousePos();

	if (mActionsMenu)
		return true;

	return (pos.x >= mBackground->Pos().x - mBackground->ScaledDimensions().x * 0.5f &&
			pos.x <= mBackground->Pos().x + mBackground->ScaledDimensions().x * 0.5f &&
			pos.y >= mBackground->Pos().y - mBackground->ScaledDimensions().y * 0.5f &&
			pos.y <= mBackground->Pos().y + mBackground->ScaledDimensions().y * 0.5f);
}

void IMenuTab::HandleLeftClick()
{
	if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::left))
	{
		if (mActionsMenu)
		{
			mCurrentAction = mActionsMenu->Action();
			if (!mCurrentAction.empty())
				SetActiveSlot(mSelectedSlot);
			mSelectedSlot = -1;
			mActionsMenu->Active(false);
		}
		else if (ContainsClick() && Active() && !InUse())
		{
			//mCurrentAction = GetAction();
			mLastClick = SDL_GetTicks();
			mLastPos = Square::InputHandler::Instance().MousePos();

			if (GetSlot(mLastPos))
				mSelectedSlot = PosToSlot(mLastPos);

		}
	}
	else if (Square::InputHandler::Instance().MouseButtonReleased(Square::InputHandler::left) && mLastClick != 0)
	{
		mLastClick = 0;

		if (SDL_GetTicks() - mLastClick <= 100 || mDragSlot == -1)
		{
			mCurrentAction = GetAction();
			SetActiveSlot(mCurrentAction.empty() ? -1 : mSelectedSlot);
			mSelectedSlot = -1;
		}

		if (mDragSlot != -1)
		{
			int swapToSlot = PosToSlot(Square::InputHandler::Instance().MousePos());

			if (swapToSlot != -1)
				Swap(mDragSlot, swapToSlot);

			mDragSlot = -1;
		}
	}
	else if (mCanDrag)
	{
		if (mLastClick != 0)
		{
			if (SDL_GetTicks() - mLastClick > 100 && mLastPos != Square::InputHandler::Instance().MousePos())
			{
				if (GetSlot(mLastPos) != nullptr)
					mDragSlot = PosToSlot(mLastPos);
			}
		}
	}
}

void IMenuTab::HandleMenus()
{
	if (mActionsMenu)
	{
		mActionsMenu->Update();

		if (!mActionsMenu->Active())
		{
			delete mActionsMenu;
			mActionsMenu = nullptr;
		}
	}
	else if (mHasHover)
	{
		if (mSelectedSlot != -1 && mSelectedSlot == mLastSlot)
		{
			mHoverTimer += Square::Timer::Instance().DeltaTime();
		}
		else
			mHoverTimer = 0.0f;

		if (Active())
			CreateTooltip();

		if (mTooltip)
		{
			mTooltip->Update();
			if (mSelectedSlot == -1 ||
				mSelectedSlot != PosToSlot(Square::InputHandler::Instance().MousePos()))
				mTooltip->Active(false);

			if (!mTooltip->Active())
			{
				delete mTooltip;
				mTooltip = nullptr;
			}
		}
	}
}

void IMenuTab::Update()
{
	mCurrentAction.clear();

	mLastSlot = mSelectedSlot;

	if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::right) && mDragSlot == -1)
	{
		if (Active() && !InUse())
		{
			CreateActionMenu();
		}
	}

	HandleLeftClick();
	HandleMenus();
}

void IMenuTab::Render()
{
	mBackground->Render(true);

	for (int i = 0; i < mSlotPos.size(); i++)
	{
		if (Square::GameObject* obj = GetSlot(i))
		{
			if (mDragSlot == i)
			{
				obj->Parent(nullptr);
				obj->Pos(Square::InputHandler::Instance().MousePos());
			}
			else
			{
				obj->Parent(this);
				obj->Pos(mSlotPos[i]);
			}

			if (IsActiveSlot(i))
				Square::Graphics::Instance().DrawRectangle(obj->Pos() - mItemSize * 0.5f, mItemSize, mItemSize, mActiveColor);

			obj->Render(true);
		}
		else if (i < mIcons.size())
			mIcons[i]->Render(true);
	}

	if (mActionsMenu) mActionsMenu->Render();
	if (mTooltip) mTooltip->Render();
}