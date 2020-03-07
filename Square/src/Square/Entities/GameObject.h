#pragma once

#include "Square/Core/Core.h"
#include "Square/Utilities/MathHelper.h"

namespace Square {

	class SQUARE_API GameObject
	{
	public:
		enum SPACE { local = 0, world = 1 };

	private:
		Vector2 mPrevPos;
		Vector2 mPos;
		float mRotation;
		Vector2 mScale;

		bool mActive;

		GameObject* mParent;

	public:
		GameObject(Vector2 pos = VEC2_ZERO);
		
		virtual ~GameObject() = default;

		Vector2 PrevPos();
		void Pos(Vector2 pos);
		Vector2 Pos(SPACE space = world);

		void Rotation(float rotation);
		float Rotation(SPACE space = world);

		void Scale(Vector2 scale);
		Vector2 Scale(SPACE space = world);

		void Active(bool active);
		bool Active();

		void Parent(GameObject* parent);
		GameObject* Parent();

		void Translate(Vector2 vec, SPACE space = world);
		void Rotate(float amount);

		virtual void Update();
		virtual void Render();

		GameObject& operator=(GameObject other);
		GameObject(const GameObject& other);
	};

}