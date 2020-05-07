#include "Timer.h"

Timer::Timer()
{
	last = std::chrono::high_resolution_clock::now();
	deltaLast = std::chrono::high_resolution_clock::now();
}

float Timer::Mark()
{
	const auto old = last;
	last = std::chrono::high_resolution_clock::now();
	const std::chrono::duration<float> frameTime = last - old;
	return frameTime.count();
}

float Timer::Peek() const
{
	return std::chrono::duration<float>(std::chrono::high_resolution_clock::now() - last).count();
}

float Timer::DeltaTime()
{
	return deltaTime;
}

void Timer::SetDeltaTime()
{
	const auto old = deltaLast;
	deltaLast = std::chrono::high_resolution_clock::now();
	deltaTime = std::chrono::duration_cast<std::chrono::milliseconds>(deltaLast - old).count() / 1000.0f;
	if (deltaTime > 0.1f)
		deltaTime = 0.1f;
}
