#pragma once

#include "Square/Core/Core.h"

namespace Square {

	class SQUARE_API Layer
	{
	public:
		Layer()
		{

		}

		virtual ~Layer() = default;

		virtual void OnUpdate() {}
		virtual void OnRender() {}
	};

}