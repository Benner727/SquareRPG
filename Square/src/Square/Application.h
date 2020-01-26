#pragma once

#include "Core.h"

namespace Square {

	class SQUARE_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	//To be defined in CLIENT
	Application* CreateApplication();

}