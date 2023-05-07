#pragma once
#include <stdint.h>

namespace PIT {
    extern double TimeSinceBoot;
    const uint64_t BaseFrequency = 1193182;

    void Sleepf(double seconds);
    void Sleep(uint64_t ms);

    void SetDivisor(uint16_t divisor);
    uint64_t GetFrequency();
    void SetFrequency(uint64_t frequency);
    void Tick();
}