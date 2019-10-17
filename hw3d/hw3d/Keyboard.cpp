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
		keyState[i] = State::RELEASED;
		keyPrevState[i] = State::NO_IMPUT;
	}
}

void Keyboard::Update()
{
	for (int i = 0; i < 256; i++)
	{
		keyPrevState[i] = keyState[i];
		if (keyState[i] == State::PRESSED || keyState[i] == State::REPEATED)
		{
			keyState[i] = State::REPEATED;
		}
		else if (keyState[i] == State::RELEASED)
		{
			keyState[i] = State::NO_IMPUT;
		}
	}
}

void Keyboard::HandlerUpdate(const UINT &msg, const WPARAM &wParam)
{
	switch (msg)
	{
	case WM_KEYDOWN:
		if (keyState[(unsigned int)wParam] == State::RELEASED || keyState[(unsigned int)wParam] == State::NO_IMPUT)
		{
			keyPrevState[(unsigned int)wParam] = keyState[(unsigned int)wParam];
			keyState[(unsigned int)wParam] = State::PRESSED;
		}
		break;
	case WM_KEYUP:
		keyState[(unsigned int)wParam] = State::RELEASED;
		break;
	}
}

bool Keyboard::IsKeyRepeated(unsigned int key)
{
	return keyState[key] == State::REPEATED;
}

bool Keyboard::IsKeyReleased(unsigned int key)
{
	return keyState[key] == State::RELEASED;
}

bool Keyboard::IsKeyPressed(unsigned int key)
{
	return keyState[key] == State::PRESSED;
}

//void Keyboard::KeyPressed(unsigned int key)
//{
//	mKeysDown[key] = true;
//}
//
//void Keyboard::KeyReleased(unsigned int key)
//{
//	mKeysDown[key] = false;
//}
//
//bool Keyboard::IsKeyDown(unsigned int key)
//{
//	return mKeysDown[key];
//}
