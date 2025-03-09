#pragma once

#include <chrono>

class Stopwatch final
{
public:
    Stopwatch() { Stop(); }
    bool IsStarted() { return bIsStarted; }
    void Stop() { bIsStarted = false; }

    void Start()
    {
        reset_time = clock.now();
        bIsStarted = true;
    }

    uint32_t Elapsed()
    {
        using elapsed_resolution = std::chrono::milliseconds;
        elapsed_resolution elapsed = std::chrono::duration_cast<elapsed_resolution>(clock.now() - reset_time);
        return (uint32_t) elapsed.count();
    }

private:
    std::chrono::high_resolution_clock clock;
    std::chrono::high_resolution_clock::time_point reset_time;
    bool bIsStarted = false;
};