#pragma once
#include <chrono>

class Time
{
public:
    static void Update();
    static double DeltaTime();

private:
	static std::chrono::steady_clock::time_point currentTime;
	static double deltaTime;
};