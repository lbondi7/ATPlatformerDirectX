#pragma once

#include <d3d11.h>
#include "dxerr.h"

#ifdef _DEBUG
#ifndef HR
#define HR(x) \
{    \
    HRESULT hr = x; \
    if (FAILED(hr)) \
    { \
        DXTraceW(__FILEW__, __LINE__, hr, L#x, TRUE); \
    }  \
}
#endif
#ifndef HR
#define HR(x) x;
#endif
#endif

class Keyboard;
class Mouse;
class Timer;
class D3D;
class Graphics;
struct Texture;
struct Misc;
struct Resources;

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

	static D3D* GetD3D() {
		return d3d;
	}

	static void InitD3D(D3D* _d3d) {
		d3d = _d3d;
	}

	static Texture* GetTexture() {
		return texture;
	}

	static void InitTexture(Texture* _texture) {
		texture = _texture;
	}

	static void InitMisc(Misc* _misc) {
		misc = _misc;
	}

	static Misc* GetMisc() {
		return misc;
	}

	static Graphics* GetGraphics(){
		return graphic;
	}

	static void InitGraphics(Graphics* _graphic){
		graphic = _graphic;
	}

	static Resources* GetResources() {
		return resources;
	}

	static void InitResources(Resources* _data) {
		resources = _data;
	}

private:
	// Static Classes
	static Keyboard* key;
	static Mouse* mouse;
	static Timer* timer;
	static D3D* d3d;
	static Graphics* graphic;
	static Texture* texture;
	static Misc* misc;
	static Resources* resources;

	// Static Variables
	static bool* exit;
};

