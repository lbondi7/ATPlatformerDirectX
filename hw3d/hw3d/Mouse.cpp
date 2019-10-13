#include "Mouse.h"

Mouse::Mouse()
{

}

Mouse::~Mouse()
{
}

void Mouse::Initialise()
{
	for (int i = 0; i < 3; i++)
	{
		buttonState[i] = State::RELEASED;
		buttonPrevState[i] = State::NO_IMPUT;
	}
	x = 0;
	y = 0;
	onScreen = false;
}

void Mouse::Update()
{
	for (int i = 0; i < 3; i++)
	{
		buttonPrevState[i] = buttonState[i];
		if (buttonState[i] == State::PRESSED || buttonState[i] == State::REPEATED)
		{
			buttonState[i] = State::REPEATED;
		}
		else if (buttonState[i] == State::RELEASED)
		{
			buttonState[i] = State::NO_IMPUT;
		}
	}
}

void Mouse::HandlerUpdate(const UINT& msg, const LPARAM& lParam, int width, int height)
{
	if (msg == WM_MOUSEMOVE)
	{
		const POINTS mousePT = MAKEPOINTS(lParam);
		if (mousePT.x > 0 && mousePT.x < width && mousePT.y > 0 && mousePT.y < height)
		{
			onScreen = true;
			SetPos(mousePT.x, mousePT.y);
		}
		else
		{
			onScreen = false;
			SetPos(mousePT.x, mousePT.y);
		}
	}

	switch (msg)
	{
	case WM_MOUSEMOVE:
	{
		const POINTS mousePT = MAKEPOINTS(lParam);
		if (mousePT.x > 0 && mousePT.x < width && mousePT.y > 0 && mousePT.y < height)
		{
			onScreen = true;
			SetPos(mousePT.x, mousePT.y);
		}
		else
		{
			onScreen = false;
			SetPos(mousePT.x, mousePT.y);
		}
		break;
	}
	case WM_LBUTTONDOWN:
	{
		if (buttonState[0] == State::RELEASED || buttonState[0] == State::NO_IMPUT)
		{
			buttonPrevState[0] = buttonState[0];
			buttonState[0] = State::PRESSED;
		}
		break;
	}
	case WM_RBUTTONDOWN:
	{
		if (buttonState[1] == State::RELEASED || buttonState[1] == State::NO_IMPUT)
		{
			buttonPrevState[1] = buttonState[1];
			buttonState[1] = State::PRESSED;
		}
		break;
	}
	case WM_LBUTTONUP:
	{
		buttonState[0] = State::RELEASED;
		break;
	}
	case WM_RBUTTONUP:
	{
		buttonState[1] = State::RELEASED;
		break;
	}
	case WM_MOUSEWHEEL:
	{
		break;
	}
	}
}

int Mouse::GetXPos()
{
	return x;
}

int Mouse::GetYPos()
{
	return y;
}

void Mouse::SetPos(int mouseX, int mouseY)
{
	x = mouseX;
	y = mouseY;
}

bool Mouse::IsOnScreen()
{
	return onScreen;
}

bool Mouse::IsButtonRepeated(unsigned int btn)
{
	return buttonState[btn] == State::REPEATED;
}

bool Mouse::IsButtonReleased(unsigned int btn)
{
	return buttonState[btn] == State::RELEASED;
}

bool Mouse::IsButtonPressed(unsigned int btn)
{
	return buttonState[btn] == State::PRESSED;
}
