#pragma once

#include <Square.h>
#include <vector>
#include <string>

class Tile : public Square::GameObject
{
private:
	bool mWalkable;
	bool mCanAttackOver;

	Square::Sprite* mTerrain;
	Square::Sprite* mFeature;
	std::vector<std::string> mCommands;

public:
	Tile(bool walkable, bool canAttackOver, Square::Sprite* terrain, Square::Sprite* feature, std::vector<std::string> commands);
	virtual ~Tile();

	inline bool Walkable() const { return mWalkable;  }
	inline bool CanAttackOver() const { return mCanAttackOver; }
	inline std::vector<std::string> const Commands() { return mCommands; }

	virtual void Update();
	virtual void Render();
};
