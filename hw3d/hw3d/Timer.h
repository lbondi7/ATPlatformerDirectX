#pragma once
#include <chrono>

class Timer
{
public:
	Timer();
	float Mark();
	float Peek() const;
	float DeltaTime();
	void SetDeltaTime();

private:
	std::chrono::steady_clock::time_point last;
	std::chrono::steady_clock::time_point deltaLast;
	std::chrono::duration<float> deltaTime;
};

