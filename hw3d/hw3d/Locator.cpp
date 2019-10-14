#include "Locator.h"

Keyboard* Locator::key = nullptr;
Mouse* Locator::mouse = nullptr;
LewisException* Locator::except = nullptr;
bool* Locator::exit = nullptr;