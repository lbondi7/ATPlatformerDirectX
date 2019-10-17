#pragma once
#include "WinSetup.h"

class Keyboard
{
public :
	Keyboard();
	~Keyboard();


	enum class State : int {
		NO_IMPUT = 0,
		PRESSED = 1,
		RELEASED = 2,
		REPEATED = 3
	};


	void Initialise();

	void Update();

	void HandlerUpdate(const UINT& msg, const WPARAM& wParam);

	//void KeyPressed(unsigned int key);

	//void KeyReleased(unsigned int key);

	bool IsKeyRepeated(unsigned int btn);

	bool IsKeyReleased(unsigned int btn);

	bool IsKeyPressed(unsigned int btn);

	//bool IsKeyDown(unsigned int key);


private:
	bool mKeyDown = false;
	bool mKeyUp = false;

	State keyState[256];
	State keyPrevState[256];
	bool mKeysDown[256];
};

