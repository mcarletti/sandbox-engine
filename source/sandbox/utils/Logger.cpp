#include <sandbox/utils/Logger.hpp>
#include <sandbox/utils/Timer.hpp>
#include <thread>
#include <fstream>
#include <sstream>
#include <execinfo.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>

namespace sb
{
    // the logfile path is relative
    // to the working directory
    std::string Logger::_log_fn = "sandbox.log";
    std::string Logger::_stack_trace_fn = "stacktrace.log";
    std::mutex Logger::_mutex;

    void Logger::write(std::string message, bool append)
    {
        std::ios::openmode flags = std::ios::in | std::ios::out;
        if (append)
            flags |= std::fstream::app;

        std::stringstream ss;
        ss << std::this_thread::get_id() << " " << Timer::getSystemTime();
        std::string text = ss.str() + " " + message + "\n";

        _mutex.lock();

        std::fstream fs;
        fs.open(_log_fn, flags);
        fs.write(text.c_str(), text.size());
        fs.close();

        _mutex.unlock();
    }

    void Logger::setSignalHandler(int signal_code)
    {
        signal(signal_code, stackTraceHandler);
    }

    void Logger::stackTraceHandler(int signal_code)
    {
        const size_t max_stack_trace_length = 100;
        void* array[max_stack_trace_length];

        // get void*'s for all entries on the stack
        size_t stack_trace_length = backtrace(array, max_stack_trace_length);

        // print out all the frames to stderr
        std::string s = "ERROR: signal " + std::to_string(signal_code) + "\n";
        write(s);

        backtrace_symbols_fd(array, stack_trace_length, STDERR_FILENO);

        FILE* fp = fopen(_stack_trace_fn.c_str(), "w");
        fprintf(fp, "%s\n", s.c_str());

        char** fun_names = backtrace_symbols(array, stack_trace_length);
        for (size_t i = 0; i < stack_trace_length; ++i)
            fprintf(fp, "%s\n", fun_names[i]);

        free(fun_names);
        fclose(fp);

        exit(EXIT_FAILURE);
    }
}