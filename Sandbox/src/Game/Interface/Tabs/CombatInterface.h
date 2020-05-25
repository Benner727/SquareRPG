#pragma once

#include "Game/Interface/Tabs/IMenuTab.h"
#include "Game/Interface/Tools/CombatButton.h"

class CombatInterface : public IMenuTab
{
private:
	Player& mPlayer;

	std::vector<std::shared_ptr<CombatButton>> mCombatButtons;
	CombatStyle mCurrentCombatStyle;

	std::string mWeaponText;
	Square::Text* mWeaponSprite;

	std::string mCombatLevelText;
	Square::Text* mCombatLevelSprite;

	std::string GetAction();

	void CreateActionMenu();
	void CreateTooltip();

	inline void SetActiveSlot(int slot);
	inline bool IsActiveSlot(int slot);
	inline void Swap(int slotOne, int slotTwo) { }
	std::shared_ptr<Square::GameObject> GetSlot(int slot, bool includeActive = true);

	void UpdateText();

	void MeleeSetup();
	void RangedSetup();
	void MagicSetup();

	void PrivateUpdate();
	void PrivateRender();

public:
	CombatInterface(Player& player);
	~CombatInterface();

	std::shared_ptr<Square::GameObject> GetSlot(Square::Vector2 pos, bool includeActive = true);
};