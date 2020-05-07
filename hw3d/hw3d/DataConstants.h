#pragma once
#include "Maths.h"

enum class ModelType {
	CUBE = 0,
	TRI = 1,
	SQUARE = 2,
	ISO = 3,
	HELI = 4,
};

enum class ShaderType : int
{
	DEFAULT = 0,
	DIR_LIGHT = 1,
	TEXTURE = 2,
	INSTANCE = 3,
};

enum  class TextureType : int
{
	SIMON = 0,
	UV = 1,
	MR_BEAN = 2
};

struct ImageDataBuffer
{
	unsigned char data1[12];
	unsigned short width;
	unsigned short height;
	unsigned char bpp;
	unsigned char data2;
};

struct ImageData
{
	ImageDataBuffer buffer;
	unsigned char* data;
};

struct LightBufferData
{
	alignas(16) DirectX::XMVECTOR diffuseColor;
	alignas(16) DirectX::XMVECTOR lightDirection;
};