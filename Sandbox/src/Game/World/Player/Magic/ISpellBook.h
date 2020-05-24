#pragma once

#include "Game/World/Player/Magic/Spell.h"

class ISpellBook
{
private:
	int mActiveSpell;
	int mAutoCastSpell;

protected:
	std::vector<std::shared_ptr<Spell>> mSpells;

public:
	ISpellBook() : mActiveSpell(-1), mAutoCastSpell(-1) {}

	virtual ~ISpellBook() = default;

	inline std::vector<std::shared_ptr<Spell>> Spells() const { return mSpells; }

	inline int ActiveSpell() const { return mActiveSpell; }
	inline void ActiveSpell(int activespell) { mActiveSpell = activespell; }

	inline std::shared_ptr<Spell> AutoCastSpell() const { return (mAutoCastSpell != -1 ? mSpells[mAutoCastSpell] : nullptr); }
	inline void AutoCastSpell(int autoCastSpell) { mAutoCastSpell = autoCastSpell; }
};