#include <sandbox/utils/Timer.hpp>
#include <thread>

namespace sb::utils
{
    // timer resolution: milliseconds, microseconds, nanoseconds
    using timeres = std::chrono::nanoseconds;

    Timer::Timer()
    {
        restart();
    }

    void Timer::restart()
    {
        _tstart = getTime();
        _tframe = _tstart;
    }

    ulong Timer::getWallTime() const
    {
        return std::chrono::duration_cast<timeres>(getTime() - _tstart).count();
    }

    ulong Timer::getFrameTime()
    {
        std::chrono::system_clock::time_point now = getTime();
        ulong t = std::chrono::duration_cast<timeres>(now - _tframe).count();
        _tframe = now;
        return t;
    }

    ulong Timer::getSystemTime()
    {
        std::chrono::system_clock::time_point now = getTime();
        ulong t = std::chrono::duration_cast<timeres>(now.time_since_epoch()).count();
        return t;
    }

    void Timer::sleep(ulong ms)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(ms));
    }

    void Timer::usleep(ulong us)
    {
        std::this_thread::sleep_for<int64_t, std::micro>(std::chrono::microseconds(us));
    }

    std::chrono::system_clock::time_point Timer::getTime()
    {
        //return std::chrono::high_resolution_clock::now();
        return std::chrono::system_clock::now();
    }
}