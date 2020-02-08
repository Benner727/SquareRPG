#pragma once

#include "Square/Core/Core.h"
#include "Square/Core/Engine.h"

namespace Square {

	class SQUARE_API Application
	{
	public:
		Application();
		virtual ~Application() = default;

		void PushLayer(Layer* layer);
		void PopLayer(Layer* layer);

		void Run();

	private:
		Engine& mEngine;
	};

	//To be defined in CLIENT
	Application* CreateApplication();

}