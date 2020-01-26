#pragma once

#ifdef SQ_PLATFORM_WINDOWS

extern Square::Application* Square::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Square::CreateApplication();
	app->Run();
	delete app;
}

#endif