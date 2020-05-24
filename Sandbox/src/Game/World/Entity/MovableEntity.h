#pragma once

#include <Square.h>

#include "Game/Point.h"

#include <list>

class MovableEntity : public Square::GameObject
{
private:
	Point mMapPosition;
	std::list<Point> mCurrentPath;
	float mMoveSpeed;
	bool mRunning;
	int mEnergy;

protected:
	inline int BaseMovementSpeed() const { return mMoveSpeed; }
	inline void BaseMovementSpeed(int speed) { mMoveSpeed = speed; }

	void HandleMovement();

public:
	MovableEntity();
	virtual ~MovableEntity() = default;

	inline Point MapPosition() const { return mMapPosition; }
	void MapPosition(Point p);

	inline std::list<Point> CurrentPath() const { return mCurrentPath; }
	
	void MoveTo(Point point);
	void PathTo(std::list<Point> path);

	void CancelMove();

	inline void Run(bool run) { mRunning = run; }
	inline bool Running() const { return mRunning; }

	inline int Energy() const { return mEnergy; }
};