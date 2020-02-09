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

Item* ItemFactory::GetItem(int index, int amount)
{
	Item* item = nullptr;

	if (mItemRepository.FindFoodDefinition(index))
	{
		item = new Food(index, amount);
		dynamic_cast<Food*>(item)->mFoodDefinition = mItemRepository.FindFoodDefinition(index);
	}
	else if (mItemRepository.FindPotionDefinition(index))
	{
		item = new Potion(index, amount);
		dynamic_cast<Potion*>(item)->mPotionDefinition = mItemRepository.FindPotionDefinition(index);
	}
	else
	{
		item = new Item(index, amount);
	}

	item->mItemDefinition = mItemRepository.FindItemDefinition(index);
	//item->mSprite = new Square::Sprite(item->mItemDefinition->SpritePath());
	//item->mSprite->Parent(item);

	return item;
}