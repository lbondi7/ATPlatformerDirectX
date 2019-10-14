#include "WinSetup.h"
#include "Window.h"
#include "Locator.h"
#include "LewisException.h"
#include "Game.h"

int CALLBACK WinMain(
HINSTANCE hInstance,
HINSTANCE hPrevInstance,
LPSTR lpCmdLine,
int nCmdShow)
{
	Game game;
	if (!game.Init())
	{
		return - 1;
	}

	game.Run();
	game.Exit();
	return -1;
	{
		//Keyboard* key = new Keyboard();
		//Locator::InitKey(key);
		//Mouse* mouse = new Mouse();
		//Locator::InitMouse(mouse);
		//Window wnd(800, 300, "Lewis' Window");

		//Locator::GetKey()->Initialise();
		//Locator::GetMouse()->Initialise();

		//// message pump
		//MSG msg;
		//BOOL gResult;
		//while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		//{
		//	TranslateMessage(&msg);
		//	DispatchMessage(&msg);


		//	if (Locator::GetKey()->IsKeyDown('C'))
		//	{
		//		wnd.SetWindowTitle("Ya MUM");
		//	}
		//	if (Locator::GetKey()->IsKeyDown(VK_DOWN))
		//	{
		//		wnd.SetWindowTitle("HEY");
		//	}

		//	if (Locator::GetMouse()->IsOnScreen())
		//	{
		//		wnd.SetWindowTitle("Mouse State: " + std::to_string((int)Locator::GetMouse()->state()));
		//	}
		//	//if (Locator::GetMouse()->IsOnScreen() && Locator::GetMouse()->IsButtonRepeated(0))
		//	//{
		//	//	wnd.SetWindowTitle("Mouse Pos: " + std::to_string(Locator::GetMouse()->GetXPos()) + ',' + std::to_string(Locator::GetMouse()->GetYPos()));
		//	//}
		//}

		//if (gResult == -1)
		//{
		//	return -1;
		//}

		//return msg.wParam;
	//catch (const LewisException& e)
	//{
	//	MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
	//}
	//catch (const std::exception& e)
	//{
	//	MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	//}
	//catch (...)
	//{
	//	MessageBox(nullptr, Locator::GetException()->What(), "Uknown Exception", MB_OK | MB_ICONEXCLAMATION);
	//}
	// 	return -1;
	}
}