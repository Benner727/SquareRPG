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
}

void ItemRepository::Init()
{
	LoadItemDefinitions();
	LoadFoodDefinitions();
	LoadPotionDefinitions();
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
		std::vector<SkillData> skillData;

		iss >> index >> replaceIndex >> restoreOnly;

		while (iss >> skillIndex >> add >> delim >> modifier)
			skillData.push_back(SkillData(skillIndex, add, modifier));

		mPotionDefinitions[index] = new PotionDefinition(index, replaceIndex, restoreOnly, skillData);
		skillData.clear();
	}

	infile.close();
	std::cout << "Potion definitions loaded: " << mPotionDefinitions.size() << std::endl;
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