#pragma once

#include "Game/Player/Prayer/IPrayerBook.h"

class StandardPrayerBook : public IPrayerBook
{
public:
	StandardPrayerBook()
	{
		mAuras.push_back(Aura(1, "Thick Skin", 1, 7.2f, AuraType::defense, "ThickSkinIcon.png"));
		mAuras.push_back(Aura(2, "Burst of Strength", 4, 7.2f, AuraType::strength, "BurstOfStrengthIcon.png"));
		mAuras.push_back(Aura(3, "Clarity of Thought", 7, 7.2f, AuraType::attack, "ClarityOfThoughtIcon.png"));
		mAuras.push_back(Aura(4, "Sharp Eye", 8, 7.2f, AuraType::mage_range, "SharpEyeIcon.png"));
		mAuras.push_back(Aura(5, "Mystic Will", 9, 7.2f, AuraType::mage_range, "MysticWillIcon.png"));
		mAuras.push_back(Aura(6, "Rock Skin", 10, 4.8f, AuraType::defense, "RockSkinIcon.png"));
		mAuras.push_back(Aura(7, "Superhuman Strength", 13, 4.8f, AuraType::strength, "SuperhumanStrengthIcon.png"));
		mAuras.push_back(Aura(8, "Improved Reflexes", 16, 4.8f, AuraType::attack, "ImprovedReflexesIcon.png"));
		mAuras.push_back(Aura(9, "Hawk Eye", 26, 4.8f, AuraType::mage_range, "HawkEyeIcon.png"));
		mAuras.push_back(Aura(10, "Mystic Lore", 27, 4.8f, AuraType::mage_range, "MysticLoreIcon.png"));
		mAuras.push_back(Aura(11, "Steel Skin", 28, 3.6f, AuraType::defense, "SteelSkinIcon.png"));
		mAuras.push_back(Aura(12, "Ultimate Strength", 31, 3.6f, AuraType::strength, "UltimateStrengthIcon.png"));
		mAuras.push_back(Aura(13, "Incredible Reflexes", 34, 3.6f, AuraType::attack, "IncredibleReflexesIcon.png"));
		mAuras.push_back(Aura(14, "Protect from Magic", 37, 2.4f, AuraType::over_head, "ProtectFromMagicIcon.png"));
		mAuras.push_back(Aura(15, "Protect from Range", 40, 2.4f, AuraType::over_head, "ProtectFromRangeIcon.png"));
		mAuras.push_back(Aura(16, "Protect from Melee", 43, 2.4f, AuraType::over_head, "ProtectFromMeleeIcon.png"));
		mAuras.push_back(Aura(17, "Eagle Eye", 44, 3.6f, AuraType::mage_range, "EagleEyeIcon.png"));
		mAuras.push_back(Aura(18, "Mystic Might", 45, 3.6f, AuraType::mage_range, "MysticMightIcon.png"));
		mAuras.push_back(Aura(19, "Chivalry", 60, 1.8f, AuraType::combat, "ChivalryIcon.png"));
		mAuras.push_back(Aura(20, "Piety", 70, 1.8f, AuraType::combat, "PietyIcon.png"));
	}

	virtual ~StandardPrayerBook() = default;
};