#pragma once
#include "WinSetup.h"

class Keyboard
{
public :
	Keyboard();
	~Keyboard();

	void Initialise();

	void Update(const UINT& msg, const WPARAM& wParam);

	void KeyPressed(unsigned int key);

	void KeyReleased(unsigned int key);

	bool IsKeyDown(unsigned int key);


private:
	bool mKeyDown = false;
	bool mKeyUp = false;

	bool mKeysDown[256];
};

