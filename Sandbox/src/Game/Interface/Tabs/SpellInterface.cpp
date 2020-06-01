#include "SpellInterface.h"

SpellInterface::SpellInterface(ISpellBook& spellBook)
	: IMenuTab("Interface/panel_brown.png", { 32, 32 }, false, true), mSpellBook(spellBook)
{
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			mSlotPos.push_back(Square::Vector2(x * 48.0f + 32.0f, y * 48.0f + 32.0f));
		}
	}
}

std::string SpellInterface::GetAction()
{
	std::string action = "";

	Square::Vector2 pos = Square::InputHandler::Instance().MousePos();

	if (Spell* spell = dynamic_cast<Spell*>(GetSlot(pos).get()))
	{
		action = "Select Spell";
	}

	return action;
}

void SpellInterface::CreateActionMenu()
{
	if (Spell* spell = dynamic_cast<Spell*>(GetSlot(Square::InputHandler::Instance().MousePos()).get()))
	{
		mActionsMenu = new ActionsMenu(spell->Name(), { "Select Spell" }, Square::InputHandler::Instance().MousePos());
		mSelectedSlot = PosToSlot(Square::InputHandler::Instance().MousePos());

		delete mTooltip;
		mTooltip = nullptr;
	}
}

void SpellInterface::CreateTooltip()
{
	if (Spell* spell = dynamic_cast<Spell*>(GetSlot(Square::InputHandler::Instance().MousePos()).get()))
	{
		mSelectedSlot = PosToSlot(Square::InputHandler::Instance().MousePos());

		if (!mTooltip && mHoverTimer > 0.5f)
		{
			std::vector<std::string> tooltipText;

			tooltipText.push_back("Level " + std::to_string(spell->LevelReq()) + ": " + spell->Name());

			for (auto req : spell->CastReq())
				tooltipText.push_back(req->Name() + " x" + std::to_string(req->Amount()));

			mTooltip = new Tooltip(tooltipText, spell->Pos() + 16.0f);
		}
	}
	else
		mSelectedSlot = -1;
}

std::shared_ptr<Square::GameObject> SpellInterface::GetSlot(int slot, bool includeActive)
{
	std::shared_ptr<Spell> spell = nullptr;
	
	if (slot >= 0 && slot < mSpellBook.CombatSpells().size())
	{
		if (includeActive || (slot != mSpellBook.ActiveSpell() && !includeActive))
		{
			spell = mSpellBook.CombatSpells()[slot];
		}
	}

	return spell;
}

std::shared_ptr<Square::GameObject> SpellInterface::GetSlot(Square::Vector2 pos, bool includeActive)
{
	int slot = PosToSlot(pos);

	return GetSlot(slot, includeActive);
}