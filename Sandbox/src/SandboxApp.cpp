#include <Square.h>

class Sandbox : public Square::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Square::Application* Square::CreateApplication()
{
	return new Sandbox();
}