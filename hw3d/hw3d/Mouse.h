#pragma once
#include "WinSetup.h"

class Mouse
{
public:

	Mouse();
	~Mouse();

	enum class State : int {
		NO_IMPUT = 0,
		PRESSED = 1,
		RELEASED = 2,
		REPEATED = 3
	};

	void Initialise();
	void Update();
	void HandlerUpdate(const UINT& msg, const LPARAM& lParam, int width, int height);

	int GetXPos();
	int GetYPos();

	void SetPos(int mouseX, int mouseY);

	bool IsOnScreen();
	bool IsButtonRepeated(unsigned int btn);

	bool IsButtonReleased(unsigned int btn);

	bool IsButtonPressed(unsigned int btn);

	State state() { return buttonState[0]; }

private:

	int x; 
	int y;
	bool onScreen = false;
	State buttonState[3];
	State buttonPrevState[3];
};

