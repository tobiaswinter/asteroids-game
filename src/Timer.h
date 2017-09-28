#pragma once
#include <chrono>

class Timer
{
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> then;
public:
    Timer() = default;
    ~Timer() = default;

    void Start() { then = std::chrono::high_resolution_clock::now(); }
    void Reset() { then = std::chrono::high_resolution_clock::now(); }

    double GetTimeDelta()
    {
        auto now = std::chrono::high_resolution_clock::now();
        auto dur = now - then;
        typedef std::chrono::duration<double> float_seconds;
        auto secs = std::chrono::duration_cast<float_seconds>(dur);

        return secs.count();
    }
};

