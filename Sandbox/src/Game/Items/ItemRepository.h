#pragma once

#include <Square.h>

#include <map>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "Game/Utility.h"

#include "Game/Definitions/ItemDefinition.h"
#include "Game/Definitions/FoodDefinition.h"
#include "Game/Definitions/PotionDefinition.h"
#include "Game/Definitions/EquipmentDefinition.h"
#include "Game/Definitions/ItemBonusDefinition.h"
#include "Game/Definitions/WeaponDefinition.h"
#include "Game/Definitions/RangedDefinition.h"

class ItemRepository
{
private:
	std::map<int, ItemDefinition*> mItemDefinitions;
	std::map<int, FoodDefinition*> mFoodDefinitions;
	std::map<int, PotionDefinition*> mPotionDefinitions;
	std::map<int, EquipmentDefinition*> mEquipmentDefinitions;
	std::map<int, ItemBonusDefinition*> mItemBonusDefinitions;
	std::map<int, WeaponDefinition*> mWeaponDefinitions;
	std::map<int, RangedDefinition*> mRangedDefinitions;

	ItemRepository();
	~ItemRepository();

	void Init();

	void LoadItemDefinitions();
	void LoadFoodDefinitions();
	void LoadPotionDefinitions();
	void LoadEquipmentDefinitions();
	void LoadItemBonusDefinitions();
	void LoadWeaponDefinitions();
	void LoadRangedDefinitions();

public:
	static ItemRepository& Instance();

	ItemDefinition* FindItemDefinition(int index);
	FoodDefinition* FindFoodDefinition(int index);
	PotionDefinition* FindPotionDefinition(int index);
	EquipmentDefinition* FindEquipmentDefinition(int index);
	ItemBonusDefinition* FindItemBonusDefinition(int index);
	WeaponDefinition* FindWeaponDefinition(int index);
	RangedDefinition* FindRangedDefinition(int index);
};