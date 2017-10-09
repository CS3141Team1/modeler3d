#include "TimeUtil.h"

#include <chrono>

#include "Types.h"

namespace Core
{

namespace Time
{

UInt64 Millis()
{
    return std::chrono::system_clock::now().time_since_epoch() / std::chrono::milliseconds(1L);
}

static const UInt64 StartTime = Millis();

Float64 Seconds()
{
    return (Millis() - StartTime) / 1000.0;
}

}

}
