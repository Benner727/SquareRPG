#pragma once

#include <Square.h>

class Skill : public Square::GameObject
{
private:
	std::string mSkillName;
	Square::Sprite* mIcon;
	Square::Text* mLevelText;

	int mExperience;
	int mEffectiveLevel;
	int mLevel;
	float mUpdateTimer;

public:
	Skill(std::string skillName, int experience = 0, int effectiveLevel = 1, int level = 1)
	{
		mSkillName = skillName;
		mIcon = new Square::Sprite("SkillIcons/" + skillName + "Icon.png");
		mIcon->Parent(this);

		mLevelText = nullptr;

		mExperience = experience;
		mEffectiveLevel = effectiveLevel;
		mLevel = level;
		mUpdateTimer = 60.0f;

		UpdateLevelText();
	}

	~Skill()
	{
		delete mIcon;
		delete mLevelText;
	}

	inline std::string SkillName() const { return mSkillName; }

	inline int Experience() const { return mExperience; }
	inline int EffectiveLevel() const { return mEffectiveLevel; }
	inline int Level() const { return mLevel; }
	inline float UpdateTimer() const { return mUpdateTimer; }

	inline void Experience(int experience) { mExperience = experience; }
	inline void EffectiveLevel(int effectiveLevel) { mEffectiveLevel = effectiveLevel; }
	inline void Level(int level) { mLevel = level; }
	inline void UpdateTimer(float updateTimer) { mUpdateTimer = updateTimer; }

	inline void UpdateLevelText()
	{
		delete mLevelText;
		mLevelText = new Square::Text(std::to_string(mEffectiveLevel) + "/" + std::to_string(mLevel), "Font/VeraMono.ttf", 12, { 255, 255, 255, 255 });
		mLevelText->Parent(this);
		mLevelText->Pos((mIcon->ScaledDimensions() + mLevelText->ScaledDimensions() * 0.5f) * Square::VEC2_RIGHT);
	}

	inline void Render(bool ignoreCamera = false)
	{ 
		mIcon->Render(ignoreCamera);
		mLevelText->Render(ignoreCamera);
	}
};