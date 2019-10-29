#include "Locator.h"

Keyboard* Locator::key = nullptr;
Mouse* Locator::mouse = nullptr;
Timer* Locator::timer = nullptr;
Buffers* Locator::buffer = nullptr;
D3D* Locator::d3d = nullptr;
Texture* Locator::texture = nullptr;
Shader* Locator::shader = nullptr;
Graphics* Locator::graphic = nullptr;

bool* Locator::exit = nullptr;