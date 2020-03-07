#pragma once

#include <Square.h>
#include <vector>
#include <string>

class Tile : public Square::GameObject
{
private:
	bool mWalkable;
	bool mCanAttackOver;

	Square::Sprite* mSprite;
	std::vector<std::string> mCommands;

	Tile(bool walkable, bool canAttackOver, std::string spritePath, std::vector<std::string> commands);
	virtual ~Tile();

	friend class Map;

public:
	inline bool Walkable() const { return mWalkable;  }
	inline bool CanTalkAttack() const { return mCanAttackOver; }
	inline std::vector<std::string> const Commands() { return mCommands; }

	virtual void Update();
	virtual void Render();
};