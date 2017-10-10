#include "TimeUtil.h"

#include <chrono>

#include "Types.h"

namespace Core
{

namespace Time
{

uint64 Millis()
{
    return std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1L);
}

static const uint64 StartTime = Millis();

float64 Seconds()
{
    return (Millis() - StartTime) / 1000.0;
}

}

}
