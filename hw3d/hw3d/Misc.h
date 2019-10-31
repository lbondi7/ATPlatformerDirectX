#pragma once
#include "Maths.h"

struct Misc
{
public:

	Float4 GetClearColour() { return clearColour; }
	void SetClearColour(const Float4& _clearColour) { clearColour = _clearColour; }

private:
	Float4 clearColour;
};