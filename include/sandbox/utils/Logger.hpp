/** @file Logger.hpp
 *  @brief Thread safe object to log messages to a text file.
 * 
 *  @author Marco Carletti
*/
#pragma once

#include <string>
#include <mutex>

namespace sb
{
    class Logger
    {
    public:

        /*!
            @brief Write a message as a new line in the logfile.

            Thread safe function. 
            Each message will be enriched by a prefix composed by 
            the thread id and the current timestamp.

            @param message String to be written in a new line in the logfile.
            @param append Enable/disable append mode.
        */
        static void write(std::string message, bool append = true);

        /*!
            @brief Setup the stack tracer on a signals.

            This function should be called at the very beginning
            of the program. Signals are catched from the that point.
            Once a signal has been sent, the logger catches it
            and prints the corresponding stack trace.

            Common signals code are:
            - SIGSEGV [code = 11] Storage with an invalid access (aka, segmentation fault).
            - SIGABRT [code =  6] A program gets abnormally terminated.
            - SIGQUIT [code =  3] A core dump gets generated and used to terminate the process.

            @param signal_code Signal code.
        */
        static void setSignalHandler(int signal_code);

    private:

        /*!
            @brief Handler to be installed in order to print stack trace.

            @param signal_code Signal code.
        */
        static void stackTraceHandler(int signal_code);

        //! Path of the log text file.
        static std::string _log_fn;

        //! Path of the stack trace text file.
        static std::string _stack_trace_fn;

        //! Mutex to make the logging thread safe.
        static std::mutex _mutex;
    };
}