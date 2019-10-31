#pragma once

class Keyboard;
class Mouse;
class Timer;
class Vertices;
class D3D;
class Graphics;
class Texture;
class Shader;
class Light;
class Matrices;
struct Misc;

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

	static Vertices* GetVertices() {
		return vertices;
	}

	static void InitVertices(Vertices* _buffer) {
		vertices = _buffer;
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

	static Shader* GetShader() {
		return shader;
	}

	static void InitShader(Shader* _shader) {
		shader = _shader;
	}

	static Light* GetLight() {
		return light;
	}

	static void InitLight(Light* _light) {
		light = _light;
	}

	static void InitMatrices(Matrices* _matrices) {
		matrices = _matrices;
	}

	static Matrices* GetMatrices() {
		return matrices;
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

private:
	// Static Classes
	static Keyboard* key;
	static Mouse* mouse;
	static Timer* timer;
	static Vertices* vertices;
	static D3D* d3d;
	static Graphics* graphic;
	static Texture* texture;
	static Shader* shader;
	static Light* light;
	static Matrices* matrices;
	static Misc* misc;

	// Static Variables
	static bool* exit;
};

