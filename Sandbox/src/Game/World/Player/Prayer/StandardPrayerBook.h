#pragma once

#include "Game/World/Player/Prayer/IPrayerBook.h"

class StandardPrayerBook : public IPrayerBook
{
public:
	StandardPrayerBook()
	{
		mAuras.push_back(std::make_shared<Aura>(1, "Thick Skin", 1, 7.2f, AuraType::defense, "PrayerIcons/ThickSkinIcon.png"));
		mAuras.push_back(std::make_shared<Aura>(2, "Burst of Strength", 4, 7.2f, AuraType::strength, "PrayerIcons/BurstOfStrengthIcon.png"));
		mAuras.push_back(std::make_shared<Aura>(3, "Clarity of Thought", 7, 7.2f, AuraType::attack, "PrayerIcons/ClarityOfThoughtIcon.png"));
		mAuras.push_back(std::make_shared<Aura>(4, "Sharp Eye", 8, 7.2f, AuraType::mage_range, "PrayerIcons/SharpEyeIcon.png"));
		mAuras.push_back(std::make_shared<Aura>(5, "Mystic Will", 9, 7.2f, AuraType::mage_range, "PrayerIcons/MysticWillIcon.png"));
		mAuras.push_back(std::make_shared<Aura>(6, "Rock Skin", 10, 4.8f, AuraType::defense, "PrayerIcons/RockSkinIcon.png"));
		mAuras.push_back(std::make_shared<Aura>(7, "Superhuman Strength", 13, 4.8f, AuraType::strength, "PrayerIcons/SuperhumanStrengthIcon.png"));
		mAuras.push_back(std::make_shared<Aura>(8, "Improved Reflexes", 16, 4.8f, AuraType::attack, "PrayerIcons/ImprovedReflexesIcon.png"));
		mAuras.push_back(std::make_shared<Aura>(9, "Hawk Eye", 26, 4.8f, AuraType::mage_range, "PrayerIcons/HawkEyeIcon.png"));
		mAuras.push_back(std::make_shared<Aura>(10, "Mystic Lore", 27, 4.8f, AuraType::mage_range, "PrayerIcons/MysticLoreIcon.png"));
		mAuras.push_back(std::make_shared<Aura>(11, "Steel Skin", 28, 3.6f, AuraType::defense, "PrayerIcons/SteelSkinIcon.png"));
		mAuras.push_back(std::make_shared<Aura>(12, "Ultimate Strength", 31, 3.6f, AuraType::strength, "PrayerIcons/UltimateStrengthIcon.png"));
		mAuras.push_back(std::make_shared<Aura>(13, "Incredible Reflexes", 34, 3.6f, AuraType::attack, "PrayerIcons/IncredibleReflexesIcon.png"));
		mAuras.push_back(std::make_shared<Aura>(14, "Protect from Magic", 37, 2.4f, AuraType::over_head, "PrayerIcons/ProtectFromMagicIcon.png"));
		mAuras.push_back(std::make_shared<Aura>(15, "Protect from Range", 40, 2.4f, AuraType::over_head, "PrayerIcons/ProtectFromRangeIcon.png"));
		mAuras.push_back(std::make_shared<Aura>(16, "Protect from Melee", 43, 2.4f, AuraType::over_head, "PrayerIcons/ProtectFromMeleeIcon.png"));
		mAuras.push_back(std::make_shared<Aura>(17, "Eagle Eye", 44, 3.6f, AuraType::mage_range, "PrayerIcons/EagleEyeIcon.png"));
		mAuras.push_back(std::make_shared<Aura>(18, "Mystic Might", 45, 3.6f, AuraType::mage_range, "PrayerIcons/MysticMightIcon.png"));
		mAuras.push_back(std::make_shared<Aura>(19, "Chivalry", 60, 1.8f, AuraType::combat, "PrayerIcons/ChivalryIcon.png"));
		mAuras.push_back(std::make_shared<Aura>(20, "Piety", 70, 1.8f, AuraType::combat, "PrayerIcons/PietyIcon.png"));
	}

	virtual ~StandardPrayerBook() = default;
};