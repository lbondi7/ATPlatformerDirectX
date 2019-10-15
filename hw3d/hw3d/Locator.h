#pragma once

class Keyboard;
class Mouse;
class Timer;

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

	static Timer* GetTimer() {
		return timer;
	}

	static void InitTimer(Timer* _timer){
		timer = _timer;
	}

	static bool* GetExitBool() {
		return exit;
	}

	static void InitExitBool(){ 
		exit = new bool;
		*exit = false;
	}

private:
	static Keyboard* key;
	static Mouse* mouse;
	static Timer* timer;
	static bool* exit;
};

