#include "Tile.h"

Tile::Tile(bool walkable, bool canAttackOver, std::string spritePath, std::vector<std::string> commands)
	: mWalkable(walkable), mCanAttackOver(canAttackOver), mCommands(commands)
{
	mSprite = new Square::Sprite(spritePath);
	mSprite->Parent(this);
}

Tile::~Tile()
{
	delete mSprite;
}

void Tile::Update()
{
	if (mSprite) mSprite->Update();
}

void Tile::Render()
{
	if (mSprite) mSprite->Render();
}
