#pragma once

#include "Game/Interface/IMenuTab.h"
#include "Game/Player/Magic/ISpellBook.h"

class MagicInterface : public IMenuTab
{
private:
	ISpellBook& mSpellBook;

	std::string GetAction();

	void CreateActionMenu();
	void CreateTooltip();

	inline void SetActiveSlot(int slot) { mSpellBook.ActiveSpell(slot); }
	inline bool IsActiveSlot(int slot) { return mSpellBook.ActiveSpell() == slot; }
	inline void Swap(int slotOne, int slotTwo) {}
	Square::GameObject* GetSlot(int slot, bool includeActive = true);

public:
	MagicInterface(ISpellBook& spellBook);
	~MagicInterface() = default;

	Square::GameObject* GetSlot(Square::Vector2 pos, bool includeActive = true);
};