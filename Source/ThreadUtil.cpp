#include "ThreadUtil.h"

#ifdef _WIN32
#include <windows.h>
#else // UNIX
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
#ifdef _WIN32
    ::Sleep(millis);
#else // UNIX
    std::this_thread::sleep_for(std::chrono::milliseconds(millis));
#endif
}

}

}
