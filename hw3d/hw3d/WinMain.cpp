#include "WinSetup.h"
#include "Window.h"
#include "Locator.h"
#include "Game.h"

int CALLBACK WinMain(
HINSTANCE hInstance,
HINSTANCE hPrevInstance,
LPSTR lpCmdLine,
int nCmdShow)
{
	try
	{
		Game game;
		if (!game.Init())
		{
			return -1;
		}

		game.Run();
		game.Exit();
	}
	catch (const LewisException & e)
	{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	}
	catch (const std::exception & e)
	{
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr, "No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return -1;
}