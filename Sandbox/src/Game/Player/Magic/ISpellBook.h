#pragma once

#include "Game/Player/Magic/Spell.h"

class ISpellBook
{
private:
	int mActiveSpell;

protected:
	std::vector<Spell*> mSpells;

public:
	ISpellBook() : mActiveSpell(-1) {}

	virtual ~ISpellBook()
	{
		for (auto& spell : mSpells)
			delete spell;
	}

	inline const std::vector<const Spell*>& Spells() const { return *reinterpret_cast<const std::vector<const Spell*>*>(&mSpells); }

	inline int ActiveSpell() const { return mActiveSpell; }
	inline void ActiveSpell(int activespell) { mActiveSpell = activespell; }
};