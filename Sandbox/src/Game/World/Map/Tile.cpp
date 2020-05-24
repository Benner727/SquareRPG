#include "Tile.h"

Tile::Tile(bool walkable, bool canAttackOver, Square::Sprite* terrain, Square::Sprite* feature, std::vector<std::string> commands)
	: mWalkable(walkable), mCanAttackOver(canAttackOver), mTerrain(terrain), mFeature(feature), mCommands(commands)
{
	if (mTerrain) mTerrain->Parent(this);
	if (mFeature) mFeature->Parent(this);
}

Tile::~Tile()
{
	delete mTerrain;
	delete mFeature;
}

void Tile::Update()
{
	if (mTerrain) mTerrain->Update();
	if (mFeature) mFeature->Update();
}

void Tile::Render()
{
	if (mTerrain) mTerrain->Render();
	if (mFeature) mFeature->Render();
}
