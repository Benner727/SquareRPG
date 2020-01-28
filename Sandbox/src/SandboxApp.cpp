#include <Square.h>

class GameLayer : public Square::Layer
{
public:
	GameLayer()
	{

	}

	~GameLayer()
	{

	}

	void OnUpdate() override
	{
		std::cout << "Update" << std::endl;
	}

	void OnRender() override
	{
		std::cout << "Render" << std::endl;
	}
};

class Sandbox : public Square::Application
{
public:
	Sandbox()
	{
		auto layer = new GameLayer;
		PushLayer(layer);
		//PopLayer(layer);
	}

	~Sandbox()
	{
		
	}
};

Square::Application* Square::CreateApplication()
{
	return new Sandbox();
}