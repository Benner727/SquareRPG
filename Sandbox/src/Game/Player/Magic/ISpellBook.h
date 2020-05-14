#pragma once

#include "Game/Player/Magic/Spell.h"

class ISpellBook
{
private:
	int mActiveSpell;

protected:
	std::vector<std::shared_ptr<Spell>> mSpells;

public:
	ISpellBook() : mActiveSpell(-1) {}

	virtual ~ISpellBook() = default;

	inline std::vector<std::shared_ptr<Spell>> Spells() const { return mSpells; }

	inline int ActiveSpell() const { return mActiveSpell; }
	inline void ActiveSpell(int activespell) { mActiveSpell = activespell; }
};