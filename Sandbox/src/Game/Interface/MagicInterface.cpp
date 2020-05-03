#include "MagicInterface.h"

MagicInterface::MagicInterface(ISpellBook& spellBook)
	: IMenuTab("Graphics/panel_brown.png", 32, false, true), mSpellBook(spellBook)
{
	for (int y = 0; y < 5; y++)
	{
		for (int x = 0; x < 4; x++)
		{
			mSlotPos.push_back(Square::Vector2(x * 48.0f + 32.0f, y * 48.0f + 32.0f));
		}
	}
}

std::string MagicInterface::GetAction()
{
	std::string action = "";

	Square::Vector2 pos = Square::InputHandler::Instance().MousePos();

	if (Spell* spell = dynamic_cast<Spell*>(GetSlot(pos)))
	{
		action = "Cast";
	}

	return action;
}

void MagicInterface::CreateActionMenu()
{
	if (Spell* spell = dynamic_cast<Spell*>(GetSlot(Square::InputHandler::Instance().MousePos())))
	{
		mActionsMenu = new ActionsMenu(spell->Name(), { "Cast" }, Square::InputHandler::Instance().MousePos());
		mSelectedSlot = PosToSlot(Square::InputHandler::Instance().MousePos());

		delete mTooltip;
		mTooltip = nullptr;
	}
}

void MagicInterface::CreateTooltip()
{
	if (Spell* spell = dynamic_cast<Spell*>(GetSlot(Square::InputHandler::Instance().MousePos())))
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

Square::GameObject* MagicInterface::GetSlot(int slot, bool includeActive)
{
	Spell* spell = nullptr;

	if (slot >= 0 && slot < mSpellBook.Spells().size())
	{
		if (includeActive || (slot != mSpellBook.ActiveSpell() && !includeActive))
			spell = mSpellBook.Spells()[slot];
	}

	return spell;
}

Square::GameObject* MagicInterface::GetSlot(Square::Vector2 pos, bool includeActive)
{
	int slot = PosToSlot(pos);

	return GetSlot(slot, includeActive);
}