#pragma once

class Keyboard;
class Mouse;
class Timer;
class Buffers;
class D3D;

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

	static Buffers* GetBuffers() {
		return buffer;
	}

	static void InitBuffers(Buffers* _buffer) {
		buffer = _buffer;
	}

	static D3D* GetD3D() {
		return d3d;
	}

	static void InitD3D(D3D* _d3d) {
		d3d = _d3d;
	}

private:
	// Static Classes
	static Keyboard* key;
	static Mouse* mouse;
	static Timer* timer;
	static Buffers* buffer;
	static D3D* d3d;

	// STatic Variables
	static bool* exit;
};

