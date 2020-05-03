#pragma once

#include "Game/Interface/IMenuTab.h"
#include "Game/Player/Skills.h"

class StatsInterface : public IMenuTab
{
private:
	Skills& mSkills;

	std::string GetAction();

	void CreateActionMenu();
	void CreateTooltip();

	inline void SetActiveSlot(int slot) {}
	inline bool IsActiveSlot(int slot) { return false; }
	inline void Swap(int slotOne, int slotTwo) {}
	Square::GameObject* GetSlot(int slot, bool includeActive = true);

public:
	StatsInterface(Skills& skills);
	~StatsInterface() = default;

	Square::GameObject* GetSlot(Square::Vector2 pos, bool includeActive = true);
};