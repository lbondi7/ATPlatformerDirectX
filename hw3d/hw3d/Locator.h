#pragma once

class Keyboard;
class Mouse;

class Locator
{
public:
	static Keyboard* GetKey() {
		return key;
	}

	static void InitKey(Keyboard* _key){
		key = _key;
	}

	static Mouse* GetMouse() {
		return mouse;
	}

	static void InitMouse(Mouse* _mouse){
		mouse = _mouse;
	}

	static void InitExitBool()
	{ 
		exit = new bool;
		*exit = false;
	}

	static bool* GetExitBool()
	{
		return exit;
	}


private:
	static Keyboard* key;
	static Mouse* mouse;
	static bool* exit;
};

