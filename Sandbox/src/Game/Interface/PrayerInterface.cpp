#include "PrayerInterface.h"

PrayerInterface::PrayerInterface(IPrayerBook& prayerBook)
	: mPrayerBook(prayerBook)
{
	mBackground = new Square::Sprite("Graphics/panel_brown.png");
	mBackground->Parent(this);
	mBackground->Pos(mBackground->ScaledDimensions() * 0.5f);

	mActionsMenu = nullptr;

	mTooltip = nullptr;

	mSelectedSlot = -1;

	mHoverTimer = 0.0f;
}

PrayerInterface::~PrayerInterface()
{
	delete mBackground;

	delete mActionsMenu;

	delete mTooltip;
}

int PrayerInterface::PosToSlot(Square::Vector2 pos)
{
	int x = (pos.x - Pos().x) / 48;;
	int y = (pos.y - Pos().y) / 48;;

	int slot = x + y * 4;

	if (slot < 0 || slot >= mPrayerBook.PrayerAuras().size())
		slot = -1;

	return slot;
}

std::string PrayerInterface::GetAction()
{
	std::string action = "";

	Square::Vector2 pos = Square::InputHandler::Instance().MousePos();

	if (Aura* aura = GetSlot(pos))
	{
		action = aura->Activated() ? "Deactivate" : "Activate";
	}

	return action;
}

bool PrayerInterface::ContainsClick() const
{
	Square::Vector2 pos = Square::InputHandler::Instance().MousePos();

	if (pos.x >= mBackground->Pos().x - mBackground->ScaledDimensions().x * 0.5f &&
		pos.x <= mBackground->Pos().x + mBackground->ScaledDimensions().x * 0.5f &&
		pos.y >= mBackground->Pos().y - mBackground->ScaledDimensions().y * 0.5f &&
		pos.y <= mBackground->Pos().y + mBackground->ScaledDimensions().y * 0.5f)
		return true;

	return false;
}

Aura* PrayerInterface::GetSlot(Square::Vector2 pos)
{
	int slot = PosToSlot(pos);

	if (slot != -1)
	{
		Aura* aura = mPrayerBook.PrayerAuras()[slot];
		if (pos.x >= aura->Pos().x - 16.0f &&
			pos.x <= aura->Pos().x + 16.0f &&
			pos.y >= aura->Pos().y - 16.0f &&
			pos.y <= aura->Pos().y + 16.0f)
		{
			return aura;
		}
	}

	return nullptr;
}

void PrayerInterface::Update()
{
	mCurrentAction.clear();

	int lastSlot = mSelectedSlot;

	if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::right))
	{
		if (Active())
		{
			if (Aura* aura = GetSlot(Square::InputHandler::Instance().MousePos()))
			{
				std::string action = aura->Activated() ? "Deactivate" : "Activate";
				mActionsMenu = new ActionsMenu(aura->Name(), { action }, Square::InputHandler::Instance().MousePos());
				mSelectedSlot = PosToSlot(Square::InputHandler::Instance().MousePos());

				delete mTooltip;
				mTooltip = nullptr;
			}
		}
	}

	if (Square::InputHandler::Instance().MouseButtonPressed(Square::InputHandler::left))
	{
		if (mActionsMenu)
		{
			mCurrentAction = mActionsMenu->Action();
			if (!mCurrentAction.empty())
				mPrayerBook.ActiveSlot(mSelectedSlot);
			mSelectedSlot = -1;
			mActionsMenu->Active(false);
		}
		else if (ContainsClick() && Active())
		{
			mCurrentAction = GetAction();
			mSelectedSlot = PosToSlot(Square::InputHandler::Instance().MousePos());
			mPrayerBook.ActiveSlot(mSelectedSlot);
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
	else
	{
		if (mSelectedSlot != -1 && mSelectedSlot == lastSlot)
		{
			mHoverTimer += Square::Timer::Instance().DeltaTime();
		}
		else
			mHoverTimer = 0.0f;

		if (Aura* aura = GetSlot(Square::InputHandler::Instance().MousePos()))
		{
			mSelectedSlot = PosToSlot(Square::InputHandler::Instance().MousePos());

			if (!mTooltip && mHoverTimer > 0.5f)
				mTooltip = new Tooltip({ "Level " + std::to_string(aura->LevelReq()), aura->Name() }, aura->Pos() + 16.0f);
		}
		else
			mSelectedSlot = -1;

		if (mTooltip)
		{
			mTooltip->Update();
			if (mSelectedSlot != PosToSlot(Square::InputHandler::Instance().MousePos()))
				mTooltip->Active(false);

			if (!mTooltip->Active())
			{
				delete mTooltip;
				mTooltip = nullptr;
			}
		}
	}
}

void PrayerInterface::Render()
{
	mBackground->Render();

	int width = 4;
	for (int y = 0; y < mPrayerBook.PrayerAuras().size() / width; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int index = x + y * width;

			if (index < mPrayerBook.PrayerAuras().size())
			{
				mPrayerBook.PrayerAuras()[index]->Parent(this);
				mPrayerBook.PrayerAuras()[index]->Pos(Square::Vector2(x * 48.0f + 32.0f, y * 48.0f + 32.0f));

				if (mPrayerBook.PrayerAuras()[index]->Activated())
					Square::Graphics::Instance().DrawRectangle(mPrayerBook.PrayerAuras()[index]->Pos() - 16.0f, 32.0f, 32.0f, { 125, 25, 25, 255 });

				mPrayerBook.PrayerAuras()[index]->Render();
			}
			else
				break;
		}
	}

	if (mActionsMenu) mActionsMenu->Render();
	if (mTooltip) mTooltip->Render();
}
