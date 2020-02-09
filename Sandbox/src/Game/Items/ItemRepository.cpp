#include "Game/Items/ItemRepository.h"

ItemRepository& ItemRepository::Instance()
{
	static ItemRepository instance;
	return instance;
}

ItemRepository::ItemRepository()
{
	Init();
}

ItemRepository::~ItemRepository()
{
	for (auto item : mItemDefinitions)
		delete item.second;

	for (auto food : mFoodDefinitions)
		delete food.second;

	for (auto potion : mPotionDefinitions)
		delete potion.second;

	for (auto equipment : mEquipmentDefinitions)
		delete equipment.second;

	for (auto itemBonus : mItemBonusDefinitions)
		delete itemBonus.second;

	for (auto weapon : mWeaponDefinitions)
		delete weapon.second;

	for (auto ranged : mRangedDefinitions)
		delete ranged.second;
}

void ItemRepository::Init()
{
	LoadItemDefinitions();
	LoadFoodDefinitions();
	LoadPotionDefinitions();
	LoadEquipmentDefinitions();
	LoadItemBonusDefinitions();
	LoadWeaponDefinitions();
	LoadRangedDefinitions();
}

void ItemRepository::LoadItemDefinitions()
{
	std::string fullPath = Square::AssetManager::Instance().GetBasePath();
	fullPath.append("Assets/Definitions/");

	std::ifstream infile(fullPath + "ItemDefinition.dat");
	if (!infile) std::cerr << "ItemDefinition.dat could not be opened!" << std::endl;
	else std::cout << "Loading item definitions..." << std::endl;

	std::string name;
	int index;
	bool stackable;
	int alchemyPrice;
	int generalPrice;
	std::string spritePath;

	while (infile >> std::quoted(name) >> index >> stackable >> alchemyPrice >> generalPrice >> spritePath)
	{
		mItemDefinitions[index] = new ItemDefinition(name, index, stackable, alchemyPrice, generalPrice, spritePath);
	}

	infile.close();
	std::cout << "Item definitions loaded: " << mItemDefinitions.size() << std::endl;
}

void ItemRepository::LoadFoodDefinitions()
{
	std::string fullPath = Square::AssetManager::Instance().GetBasePath();
	fullPath.append("Assets/Definitions/");

	std::ifstream infile(fullPath + "FoodDefinition.dat");
	if (!infile) std::cerr << "FoodDefinition.dat could not be opened!" << std::endl;
	else std::cout << "Loading food definitions..." << std::endl;

	int index;
	int replaceIndex;
	int healAmount;

	while (infile >> index >> replaceIndex >> healAmount)
	{
		mFoodDefinitions[index] = new FoodDefinition(index, replaceIndex, healAmount);
	}

	infile.close();
	std::cout << "Food definitions loaded: " << mFoodDefinitions.size() << std::endl;
}

void ItemRepository::LoadPotionDefinitions()
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/Definitions/");

	std::ifstream infile(fullPath + "PotionDefinition.dat", std::ifstream::in);
	if (!infile) std::cerr << "PotionDefinition.dat could not be opened!" << std::endl;
	else std::cout << "Loading potion definitions..." << std::endl;

	std::string line;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int index;
		int replaceIndex;
		bool restoreOnly;
		int skillIndex, add;
		double modifier;
		char delim = ',';
		std::vector<SkillBoost> skillBoost;

		iss >> index >> replaceIndex >> restoreOnly;

		while (iss >> skillIndex >> add >> delim >> modifier)
			skillBoost.push_back(SkillBoost(skillIndex, add, modifier));

		mPotionDefinitions[index] = new PotionDefinition(index, replaceIndex, restoreOnly, skillBoost);
		skillBoost.clear();
	}

	infile.close();
	std::cout << "Potion definitions loaded: " << mPotionDefinitions.size() << std::endl;
}

void ItemRepository::LoadEquipmentDefinitions()
{
	std::string fullPath = SDL_GetBasePath();
	fullPath.append("Assets/Definitions/");

	std::ifstream infile(fullPath + "EquipmentDefinition.dat", std::ifstream::in);
	if (!infile) std::cerr << "EquipmentDefinition.dat could not be opened!" << std::endl;
	else std::cout << "Loading equipment definitions..." << std::endl;

	std::string line;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int index;
		int slot;
		int skillIndex, level;
		char delim = ',';
		std::vector<SkillRequirement> skillRequirement;

		iss >> index >> slot;

		while (iss >> skillIndex >> delim >> level)
			skillRequirement.push_back(SkillRequirement(skillIndex, level));

		mEquipmentDefinitions[index] = new EquipmentDefinition(index, slot, skillRequirement);
		skillRequirement.clear();
	}

	infile.close();
	std::cout << "Equipment definitions loaded: " << mEquipmentDefinitions.size() << std::endl;
}

void ItemRepository::LoadItemBonusDefinitions()
{
	std::string fullPath = Square::AssetManager::Instance().GetBasePath();
	fullPath.append("Assets/Definitions/");

	std::ifstream infile(fullPath + "ItemBonusDefinition.dat");
	if (!infile) std::cerr << "ItemBonusDefinition.dat could not be opened!" << std::endl;
	else std::cout << "Loading item bonus definitions..." << std::endl;

	std::string line;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int index;
		std::array<int, ItemBonusDefinition::ItemBonus::TOTAL_BONUSES> bonuses;

		iss >> index;

		for (int i = 0; i < ItemBonusDefinition::ItemBonus::TOTAL_BONUSES; i++)
			iss >> bonuses[i];

		mItemBonusDefinitions[index] = new ItemBonusDefinition(index, bonuses);
	}

	infile.close();
	std::cout << "ItemBonus definitions loaded: " << mItemBonusDefinitions.size() << std::endl;
}

void ItemRepository::LoadWeaponDefinitions()
{
	std::string fullPath = Square::AssetManager::Instance().GetBasePath();
	fullPath.append("Assets/Definitions/");

	std::ifstream infile(fullPath + "WeaponDefinition.dat");
	if (!infile) std::cerr << "WeaponDefinition.dat could not be opened!" << std::endl;
	else std::cout << "Loading weapon definitions..." << std::endl;

	int index;
	bool twoHanded;
	float speed;
	int reach;

	while (infile >> index >> twoHanded >> speed >> reach)
	{
		mWeaponDefinitions[index] = new WeaponDefinition(index, twoHanded, speed, reach);
	}

	infile.close();
	std::cout << "Weapon definitions loaded: " << mWeaponDefinitions.size() << std::endl;
}

void ItemRepository::LoadRangedDefinitions()
{
	std::string fullPath = Square::AssetManager::Instance().GetBasePath();
	fullPath.append("Assets/Definitions/");

	std::ifstream infile(fullPath + "RangedDefinition.dat");
	if (!infile) std::cerr << "RangedDefinition.dat could not be opened!" << std::endl;
	else std::cout << "Loading ranged definitions..." << std::endl;

	std::string line;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int index;
		int type;
		int ammo;
		std::vector<int> ammoIndex;

		iss >> index >> type;

		while (iss >> ammo)
			ammoIndex.push_back(ammo);

		mRangedDefinitions[index] = new RangedDefinition(index, type, ammoIndex);
	}

	infile.close();
	std::cout << "Ranged definitions loaded: " << mRangedDefinitions.size() << std::endl;
}

ItemDefinition* ItemRepository::FindItemDefinition(int index)
{
	return mItemDefinitions[index];
}

FoodDefinition* ItemRepository::FindFoodDefinition(int index)
{
	return mFoodDefinitions[index];
}

PotionDefinition* ItemRepository::FindPotionDefinition(int index)
{
	return mPotionDefinitions[index];
}

EquipmentDefinition* ItemRepository::FindEquipmentDefinition(int index)
{
	return mEquipmentDefinitions[index];
}

ItemBonusDefinition* ItemRepository::FindItemBonusDefinition(int index)
{
	return mItemBonusDefinitions[index];
}

WeaponDefinition* ItemRepository::FindWeaponDefinition(int index)
{
	return mWeaponDefinitions[index];
}

RangedDefinition* ItemRepository::FindRangedDefinition(int index)
{
	return mRangedDefinitions[index];
}