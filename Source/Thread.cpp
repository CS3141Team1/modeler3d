#include "Thread.h"

#include <chrono>
#include <thread>

namespace Core
{

namespace Thread
{

void Sleep(UInt64 millis)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(millis));
}

}

}
