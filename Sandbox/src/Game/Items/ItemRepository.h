#pragma once

#include <Square.h>

#include <map>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>

#include "Game/Definitions/ItemDefinition.h"
#include "Game/Definitions/FoodDefinition.h"
#include "Game/Definitions/PotionDefinition.h"

class ItemRepository
{
private:
	std::map<int, ItemDefinition*> mItemDefinitions;
	std::map<int, FoodDefinition*> mFoodDefinitions;
	std::map<int, PotionDefinition*> mPotionDefinitions;

	ItemRepository();
	~ItemRepository();

	void Init();

	void LoadItemDefinitions();
	void LoadFoodDefinitions();
	void LoadPotionDefinitions();

public:
	static ItemRepository& Instance();

	ItemDefinition* FindItemDefinition(int index);
	FoodDefinition* FindFoodDefinition(int index);
	PotionDefinition* FindPotionDefinition(int index);
};