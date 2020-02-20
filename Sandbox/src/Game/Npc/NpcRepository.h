#pragma once

#include <Square.h>

#include <map>
#include <fstream>
#include <iomanip>
#include <iostream>

#include "Game/Utility.h"

#include "Game/Definitions/NpcDefinition.h"
#include "Game/Definitions/NpcCombatDefinition.h"
#include "Game/Definitions/NpcDropDefinition.h"
#include "Game/Definitions/NpcShopDefinition.h"

class NpcRepository
{
private:
	std::map<int, NpcDefinition*> mNpcDefinitions;
	std::map<int, NpcCombatDefinition*> mNpcCombatDefinitions;
	std::map<int, NpcDropDefinition*> mNpcDropDefinitions;
	std::map<int, NpcShopDefinition*> mNpcShopDefinitions;

	NpcRepository();
	~NpcRepository();

	void Init();

	void LoadNpcDefinitions();
	void LoadNpcCombatDefinitions();
	void LoadNpcDropDefinitions();
	void LoadNpcShopDefinitions();

public:
	static NpcRepository& Instance();

	NpcDefinition* FindNpcDefinition(int index);
	NpcCombatDefinition* FindNpcCombatDefinition(int index);
	NpcDropDefinition* FindNpcDropDefinition(int index);
	NpcShopDefinition* FindNpcShopDefinition(int index);
};