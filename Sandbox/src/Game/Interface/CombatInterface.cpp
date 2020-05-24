#include "CombatInterface.h"

CombatInterface::CombatInterface(Player& player)
	: IMenuTab("Graphics/panel_brown.png", { 80, 40 }, false, false), mPlayer(player)
{
	mSlotPos.push_back({ 60, 100 });
	mSlotPos.push_back({ 150, 100 });
	mSlotPos.push_back({ 60, 160 });
	mSlotPos.push_back({ 150, 160 });

	mWeaponText = "";
	mWeaponSprite = nullptr;

	mCombatLevelText = "";
	mCombatLevelSprite = nullptr;

	UpdateText();

	mCurrentCombatStyle = CombatStyle::none;
	PrivateUpdate();
}

CombatInterface::~CombatInterface()
{
	delete mWeaponSprite;
	delete mCombatLevelSprite;
}


std::string CombatInterface::GetAction()
{
	std::string action = "";

	Square::Vector2 pos = Square::InputHandler::Instance().MousePos();

	if (CombatButton* button = dynamic_cast<CombatButton*>(GetSlot(pos).get()))
	{
		action = "Set Combat Stance";
	}

	return action;
}

void CombatInterface::CreateActionMenu()
{

}

void CombatInterface::CreateTooltip()
{

}

inline void CombatInterface::SetActiveSlot(int slot)
{
	if (slot != -1)
	{
		for (int i = 0; i < mCombatButtons.size(); i++)
			mCombatButtons[i]->Selected(false);

		mCombatButtons[slot]->Selected(true);
		mPlayer.GetCombatStance().Set(mCombatButtons[slot]->GetCombatOption());
	}
}

inline bool CombatInterface::IsActiveSlot(int slot)
{
	if (slot != -1 && slot < mCombatButtons.size())
	{
		return mCombatButtons[slot]->Selected();
	}

	return false;
}

std::shared_ptr<Square::GameObject> CombatInterface::GetSlot(int slot, bool includeActive)
{
	std::shared_ptr<CombatButton> button = nullptr;

	if (slot != -1 && slot < mCombatButtons.size())
	{
		button = mCombatButtons[slot];
	}

	return button;
}

void CombatInterface::UpdateText()
{
	std::string weaponText = "Unarmed";
	if (Weapon* weapon = dynamic_cast<Weapon*>(mPlayer.Gear().GetItem(Gear::EquipmentSlot::weapon).get()))
		weaponText = weapon->Name();

	if (mWeaponText != weaponText)
	{
		mWeaponText = weaponText;
		delete mWeaponSprite;
		mWeaponSprite = new Square::Text(mWeaponText, "Font/VeraMono.ttf", 16, { 255, 255, 255, 255 });
		mWeaponSprite->Parent(this);
		mWeaponSprite->Pos(Square::Vector2(104.0f, 25.0f));
	}

	std::string combatLevelText = "Combat Level: " + std::to_string(mPlayer.Skills().CombatLevel());
	
	if (mCombatLevelText != combatLevelText)
	{
		mCombatLevelText = combatLevelText;
		delete mCombatLevelSprite;
		mCombatLevelSprite = new Square::Text(mCombatLevelText, "Font/VeraMono.ttf", 12, { 255, 255, 255, 255 });
		mCombatLevelSprite->Parent(this);
		mCombatLevelSprite->Pos(Square::Vector2(104.0f, 50.0f));
	}
}

void CombatInterface::MeleeSetup()
{
	mCombatButtons.clear();
	mCombatButtons.push_back(std::make_shared<CombatButton>("Accurate", CombatOption::melee_accurate));
	mCombatButtons.push_back(std::make_shared<CombatButton>("Aggressive", CombatOption::melee_aggressive));
	mCombatButtons.push_back(std::make_shared<CombatButton>("Controlled", CombatOption::melee_controlled));
	mCombatButtons.push_back(std::make_shared<CombatButton>("Defensive", CombatOption::melee_defensive));

	for (auto& button : mCombatButtons)
	{
		if (button->GetCombatOption() == mPlayer.GetCombatStance().Get())
			button->Selected(true);
	}
}

void CombatInterface::RangedSetup()
{
	mCombatButtons.clear();
	mCombatButtons.push_back(std::make_shared<CombatButton>("Accurate", CombatOption::ranged_accurate));
	mCombatButtons.push_back(std::make_shared<CombatButton>("Rapid", CombatOption::ranged_rapid));
	mCombatButtons.push_back(std::make_shared<CombatButton>("Longrange", CombatOption::ranged_longrange));

	for (auto& button : mCombatButtons)
	{
		if (button->GetCombatOption() == mPlayer.GetCombatStance().Get())
			button->Selected(true);
	}
}

void CombatInterface::MagicSetup()
{
	mCombatButtons.clear();
	mCombatButtons.push_back(std::make_shared<CombatButton>("Standard", CombatOption::magic_standard));
	mCombatButtons.push_back(std::make_shared<CombatButton>("Defensive", CombatOption::magic_defensive));

	for (auto& button : mCombatButtons)
	{
		if (button->GetCombatOption() == mPlayer.GetCombatStance().Get())
			button->Selected(true);
	}
}

void CombatInterface::PrivateUpdate()
{
	UpdateText();

	if (mCurrentCombatStyle != mPlayer.GetCombatStance().GetCombatStyle())
	{
		mCurrentCombatStyle = mPlayer.GetCombatStance().GetCombatStyle();

		switch (mCurrentCombatStyle)
		{
		case CombatStyle::melee:
			MeleeSetup();
			break;
		case CombatStyle::ranged:
			RangedSetup();
			break;
		case CombatStyle::magic:
			MagicSetup();
			break;
		default:
			MeleeSetup();
		}
	}
}

void CombatInterface::PrivateRender()
{
	if (mWeaponSprite) mWeaponSprite->Render(true);
	if (mCombatLevelSprite) mCombatLevelSprite->Render(true);
}

std::shared_ptr<Square::GameObject> CombatInterface::GetSlot(Square::Vector2 pos, bool includeActive)
{
	int slot = PosToSlot(pos);

	return GetSlot(slot, includeActive);
}
