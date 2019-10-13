#include "Keyboard.h"

Keyboard::Keyboard()
{
}

Keyboard::~Keyboard()
{
}

void Keyboard::Initialise()
{
	for (int i = 0; i < 256; i++)
	{
		mKeysDown[i] = false;
	}
}

void Keyboard::Update(const UINT &msg, const WPARAM &wParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		KeyPressed((unsigned int)wParam);
		break;
	case WM_KEYUP:
		KeyReleased((unsigned int)wParam);
		break;
	}
}

void Keyboard::KeyPressed(unsigned int key)
{
	mKeysDown[key] = true;
}

void Keyboard::KeyReleased(unsigned int key)
{
	mKeysDown[key] = false;
}

bool Keyboard::IsKeyDown(unsigned int key)
{
	return mKeysDown[key];
}
