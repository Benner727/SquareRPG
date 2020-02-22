#include "Game/Npc/NpcRepository.h"

NpcRepository& NpcRepository::Instance()
{
	static NpcRepository instance;
	return instance;
}

NpcRepository::NpcRepository()
{
	Init();
}

NpcRepository::~NpcRepository()
{
	for (auto npc : mNpcDefinitions)
		delete npc.second;

	for (auto npc : mNpcCombatDefinitions)
		delete npc.second;

	for (auto npc : mNpcDropDefinitions)
		delete npc.second;

	for (auto npc : mNpcShopDefinitions)
		delete npc.second;
}

void NpcRepository::Init()
{
	LoadNpcDefinitions();
	LoadNpcCombatDefinitions();
	LoadNpcDropDefinitions();
	LoadNpcShopDefinitions();
}

void NpcRepository::LoadNpcDefinitions()
{
	std::string fullPath = Square::AssetManager::Instance().GetBasePath();
	fullPath.append("Assets/Definitions/");

	std::ifstream infile(fullPath + "NpcDefinition.dat");
	if (!infile) std::cerr << "NpcDefinition.dat could not be opened!" << std::endl;
	else std::cout << "Loading npc definitions..." << std::endl;

	int index;
	std::string name;
	std::string spritePath;
	std::string actions;

	while (infile >> index >> std::quoted(name) >>  spritePath >> std::quoted(actions))
	{
		mNpcDefinitions[index] = new NpcDefinition(index, name, spritePath, DelimitedStringToVector(actions));
	}

	infile.close();
	std::cout << "Npc definitions loaded: " << mNpcDefinitions.size() << std::endl;
}

void NpcRepository::LoadNpcCombatDefinitions()
{
	std::string fullPath = Square::AssetManager::Instance().GetBasePath();
	fullPath.append("Assets/Definitions/");

	std::ifstream infile(fullPath + "NpcCombatDefinition.dat");
	if (!infile) std::cerr << "NpcCombatDefinition.dat could not be opened!" << std::endl;
	else std::cout << "Loading npc combat definitions..." << std::endl;

	std::string line;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int index;
		float respawnTime;
		bool aggressive;
		bool poisonous;
		int level;
		int hitpoints;
		int maxHit;
		float attackSpeed;
		int combatStyle;
		int weakness;
		std::array<int, 5> stats;
		std::array<int, 6> bonuses;

		iss >> index >> respawnTime >> aggressive >> poisonous >> level >> hitpoints >> maxHit
			>> attackSpeed >> combatStyle >> weakness;

		for (int i = 0; i < 5; i++)
			iss >> stats[i];

		for (int i = 0; i < 6; i++)
			iss >> bonuses[i];

		mNpcCombatDefinitions[index] = new NpcCombatDefinition(index, respawnTime, aggressive, poisonous, 
			level, hitpoints, maxHit, attackSpeed, combatStyle, weakness, stats, bonuses);
	}

	infile.close();
	std::cout << "Npc combat definitions loaded: " << mNpcCombatDefinitions.size() << std::endl;
}

void NpcRepository::LoadNpcDropDefinitions()
{
	std::string fullPath = Square::AssetManager::Instance().GetBasePath();
	fullPath.append("Assets/Definitions/");

	std::ifstream infile(fullPath + "NpcDropDefinition.dat");
	if (!infile) std::cerr << "NpcDropDefinition.dat could not be opened!" << std::endl;
	else std::cout << "Loading npc drop definitions..." << std::endl;

	std::string line;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int index;
		int itemIndex;
		int weight;
		int minAmount;
		int maxAmount;
		std::vector<WeightedDrop> drops;

		iss >> index;

		while (iss >> itemIndex >> weight >> minAmount >> maxAmount)
		{
			drops.push_back(WeightedDrop(itemIndex, weight, minAmount, maxAmount));
		}

		if (mNpcDropDefinitions[index] == nullptr)
			mNpcDropDefinitions[index] = new NpcDropDefinition(index, drops);
		else
			mNpcDropDefinitions[index]->mDrops.insert(std::end(mNpcDropDefinitions[index]->mDrops), std::begin(drops), std::end(drops));
		
		drops.clear();
	}

	infile.close();
	std::cout << "Npc drop definitions loaded: " << mNpcDropDefinitions.size() << std::endl;
}

void NpcRepository::LoadNpcShopDefinitions()
{
	std::string fullPath = Square::AssetManager::Instance().GetBasePath();
	fullPath.append("Assets/Definitions/");

	std::ifstream infile(fullPath + "NpcShopDefinition.dat");
	if (!infile) std::cerr << "NpcShopDefinition.dat could not be opened!" << std::endl;
	else std::cout << "Loading npc shop definitions..." << std::endl;

	std::string line;

	while (std::getline(infile, line))
	{
		std::istringstream iss(line);
		int index;
		std::string name;
		bool buysAll;
		int stockIndex;
		int stockAmount;
		std::vector<ItemStock> stock;

		iss >> index >> std::quoted(name) >> buysAll;

		while (iss >> stockIndex >> stockAmount)
			stock.push_back(ItemStock(stockIndex, stockAmount));

		mNpcShopDefinitions[index] = new NpcShopDefinition(index, name, buysAll, stock);

		stock.clear();
	}

	infile.close();
	std::cout << "Npc shop definitions loaded: " << mNpcShopDefinitions.size() << std::endl;
}

NpcDefinition* NpcRepository::FindNpcDefinition(int index)
{
	return mNpcDefinitions[index];
}

NpcCombatDefinition* NpcRepository::FindNpcCombatDefinition(int index)
{
	return mNpcCombatDefinitions[index];
}

NpcDropDefinition* NpcRepository::FindNpcDropDefinition(int index)
{
	return mNpcDropDefinitions[index];
}

NpcShopDefinition* NpcRepository::FindNpcShopDefinition(int index)
{
	return mNpcShopDefinitions[index];
}
