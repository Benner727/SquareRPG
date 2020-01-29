#include <Square.h>
#include <Square/Core/EntryPoint.h>

#include "GameLayer.h"

class Sandbox : public Square::Application
{
public:
	Sandbox()
	{
		auto layer = new GameLayer();
		PushLayer(layer);
	}

	~Sandbox()
	{
		
	}
};

Square::Application* Square::CreateApplication()
{
	return new Sandbox();
}