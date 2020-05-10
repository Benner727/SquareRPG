#include "MovableEntity.h"


MovableEntity::MovableEntity()
{
	mMapPosition = Point(Pos());
	mMoveSpeed = 64.0f;
	mRunning = false;
	mEnergy = 100;
}

void MovableEntity::HandleMovement()
{
	int speed = mMoveSpeed;
	if (mRunning)
		speed *= 2;

	if (mCurrentPath.size())
	{
		mMapPosition = mCurrentPath.front();
		Square::Vector2 endPosition = Square::Vector2(mMapPosition.x * 32 + 16, mMapPosition.y * 32 + 16);

		if ((Pos() - endPosition).Magnitude() >= speed * Square::Timer::Instance().DeltaTime())
		{
			Square::Vector2 direction = (endPosition - Pos()).Normalize();
			float angle = atan2(direction.y, direction.x) * RAD_TO_DEG;
			Translate(Square::RotateVector(speed * Square::Timer::Instance().DeltaTime(), angle));
		}
		else
		{
			mCurrentPath.pop_front();
		}

		if (mCurrentPath.size() < 1)
			Pos(endPosition);
	}
}

void MovableEntity::MoveTo(Point point)
{
	mCurrentPath.clear();
	mCurrentPath.push_back(point);
}

void MovableEntity::PathTo(std::list<Point> path)
{
	mCurrentPath.clear();
	mCurrentPath = path;
}

void MovableEntity::CancelMove()
{
	mCurrentPath.clear();
}
