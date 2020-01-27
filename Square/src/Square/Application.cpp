#include "Application.h"

#include "Engine.h"

namespace Square {

Application::Application()
{
}


Application::~Application()
{
}

void Application::Run()
{
	auto& engine = Engine::Instance();

	engine.Run();
}

}