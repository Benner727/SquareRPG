#include "Application.h"

namespace Square {

	Application::Application()
		: mEngine(Engine::Instance())
	{
		
	}


	Application::~Application()
	{
	}

	void Application::PushLayer(Layer* layer)
	{
		mEngine.PushLayer(layer);
	}

	void Application::PopLayer(Layer* layer)
	{
		mEngine.PopLayer(layer);
	}

	void Application::Run()
	{
		mEngine.Run();
	}

}