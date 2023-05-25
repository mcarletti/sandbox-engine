/** @file Timer.hpp
 *  @brief High resolution timer based on chrono.
 * 
 *  Chrono utility to get the current timestamp and compute
 *  application time intervals such as frame and wall time.
 * 
 *  @author Marco Carletti
*/
#pragma once

#include <sandbox/core/types.hpp>
#include <chrono>

namespace sb::utils
{
    class Timer
    {
    public:

        //! Constructor.
        Timer();

        //! Reset timer.
        void restart();

        //! Return time from timer creation or last reset.
        ulong getWallTime() const;

        /*!
            @brief Return elapsed time from last call.

            Return elapsed time from last call of 'getFrameTime' function 
            or from the timer creation (if first call).
        */
        ulong getFrameTime();

        //! Return system time in nanoseconds.
        static ulong getSystemTime();

        //! Sleep calling thread for 'ms' milliseconds.
        static void sleep(ulong ms);

        //! Sleep calling thread for 'us' microiseconds.
        static void usleep(ulong us);

    private:

        //! Retrieve current system clock.
        static std::chrono::system_clock::time_point getTime();

        //! Reference time (t0).
        std::chrono::system_clock::time_point _tstart;

        //! Reference time used to compute the 'getFrameTime' delta.
        std::chrono::system_clock::time_point _tframe;
    };
}