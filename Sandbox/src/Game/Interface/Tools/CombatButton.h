#pragma once

#include <Square.h>

#include "Game/World/Player/Player.h"

class CombatButton : public Square::GameObject
{
private:
	Square::Sprite* mDefaultSprite;
	Square::Sprite* mSelectedSprite;
	Square::Text* mText;

	CombatOption mCombatOption;

	bool mSelected;

public:
	CombatButton(std::string text, CombatOption combatOption)
		: mCombatOption(combatOption), mSelected(false)
	{
		mDefaultSprite = new Square::Sprite("Graphics/button_default.png");
		mDefaultSprite->Parent(this);

		mSelectedSprite = new Square::Sprite("Graphics/button_selected.png");
		mSelectedSprite->Parent(this);

		mText = new Square::Text(text, "Font/VeraMono.ttf", 12, { 0, 0, 0, 255 });
		mText->Parent(this);
	}
	
	~CombatButton()
	{
		delete mDefaultSprite;
		delete mSelectedSprite;
		delete mText;
	}

	inline CombatOption GetCombatOption() const { return mCombatOption; }
	inline void SetCombatOption(CombatOption combatOption) { mCombatOption = combatOption; }

	inline bool Selected() const { return mSelected; }
	inline void Selected(bool selected) { mSelected = selected; }

	void Render(bool ignoreCamera = false)
	{
		mSelected ? mSelectedSprite->Render(ignoreCamera) : mDefaultSprite->Render(ignoreCamera);
		mText->Render(ignoreCamera); 
	}
};