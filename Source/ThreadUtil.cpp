#include "ThreadUtil.h"

#ifndef _WIN32
#include <chrono>
#include <thread>
#endif

#include "Types.h"

namespace Core
{

namespace Thread
{

void Sleep(uint64 millis)
{
#ifndef _WIN32
    std::this_thread::sleep_for(std::chrono::milliseconds(millis));
#endif
}

}

}
