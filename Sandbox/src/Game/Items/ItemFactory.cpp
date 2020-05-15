#include "Game/Items/ItemFactory.h"

ItemFactory& ItemFactory::Instance()
{
	static ItemFactory instance;
	return instance;
}

ItemFactory::ItemFactory()
	: mItemRepository(ItemRepository::Instance())
{

}

ItemFactory::~ItemFactory()
{

}

std::shared_ptr<Item> ItemFactory::GetItem(int index, int amount)
{
	std::shared_ptr<Item> item;

	if (mItemRepository.FindFoodDefinition(index))
	{
		item = std::make_shared<Food>(Food(index, amount));
		std::dynamic_pointer_cast<Food>(item)->mFoodDefinition = mItemRepository.FindFoodDefinition(index);
	}
	else if (mItemRepository.FindPotionDefinition(index))
	{
		item = std::make_shared<Potion>(Potion(index, amount));
		std::dynamic_pointer_cast<Potion>(item)->mPotionDefinition = mItemRepository.FindPotionDefinition(index);
	}
	else if (mItemRepository.FindEquipmentDefinition(index))
	{
		if (mItemRepository.FindWeaponDefinition(index))
		{
			item = std::make_shared<Weapon>(Weapon(index, amount));

			std::dynamic_pointer_cast<Weapon>(item)->mWeaponDefinition = mItemRepository.FindWeaponDefinition(index);
			std::dynamic_pointer_cast<Weapon>(item)->mRangedDefinition = mItemRepository.FindRangedDefinition(index);
		}
		else
			item = std::make_shared<Equipment>(Equipment(index, amount));

		std::dynamic_pointer_cast<Equipment>(item)->mItemBonusDefinition = mItemRepository.FindItemBonusDefinition(index);
		std::dynamic_pointer_cast<Equipment>(item)->mEquipmentDefinition = mItemRepository.FindEquipmentDefinition(index);
	}
	else
	{
		item = std::make_shared<Item>(Item(index, amount));
	}

	item->mItemDefinition = mItemRepository.FindItemDefinition(index);
	item->mSprite = new Square::Sprite("Items/" + item->mItemDefinition->SpritePath());
	item->mSprite->Parent(item.get());

	return item;
}