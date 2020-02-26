#pragma once

#include <Square.h>

#include "Game/Definitions/NpcDefinition.h"
#include "Game/Definitions/NpcCombatDefinition.h"
#include "Game/Definitions/NpcDropDefinition.h"

class Npc : public Square::GameObject
{
private:
	int mIndex;

	Square::Sprite* mSprite;

	NpcDefinition* mNpcDefinition;

protected:
	Npc(int index);

	friend class NpcFactory;

public:
	~Npc();

	inline int Index() const { return mNpcDefinition->Index(); }
	inline std::string Name() const { return mNpcDefinition->Name(); }
	inline std::vector<std::string> Actions() const { return mNpcDefinition->Actions(); }

	void Render();
};