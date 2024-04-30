#include "Utils/Time.h"

std::chrono::steady_clock::time_point Time::currentTime = std::chrono::steady_clock::time_point();
double Time::deltaTime = 0.0;

void Time::Update()
{
    std::chrono::duration<double> newEnd = std::chrono::steady_clock::now() - currentTime;
    currentTime = std::chrono::steady_clock::now();

    deltaTime = newEnd.count();
}

double Time::DeltaTime()
{
    return deltaTime;
}