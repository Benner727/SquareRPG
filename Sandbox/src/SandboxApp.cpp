#include <Square.h>
#include <Square/Core/EntryPoint.h>

#include "GameLayer.h"
#include "Game/Items/ItemFactory.h"
#include "Game/Player/Player.h"
#include "Game/Commands/EatCommand.h"
#include "Game/Commands/CommandManager.h"

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