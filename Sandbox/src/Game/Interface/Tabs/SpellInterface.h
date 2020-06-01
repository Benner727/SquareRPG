#pragma once

#include "Game/Interface/Tabs/IMenuTab.h"
#include "Game/World/Player/Magic/ISpellBook.h"

class SpellInterface : public IMenuTab
{
private:
	ISpellBook& mSpellBook;

	std::string GetAction();

	void CreateActionMenu();
	void CreateTooltip();

	inline void SetActiveSlot(int slot) { mSpellBook.ActiveSpell(slot); }
	inline bool IsActiveSlot(int slot) { return mSpellBook.AutoCastSpell() == std::dynamic_pointer_cast<Spell>(GetSlot(slot)); }
	inline void Swap(int slotOne, int slotTwo) {}
	std::shared_ptr<Square::GameObject> GetSlot(int slot, bool includeActive = true);

public:
	SpellInterface(ISpellBook& spellBook);
	~SpellInterface() = default;

	std::shared_ptr<Square::GameObject> GetSlot(Square::Vector2 pos, bool includeActive = true);
};