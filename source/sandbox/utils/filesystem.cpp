#include <sandbox/utils/filesystem.hpp>
#include <stdexcept>
#include <fstream>

namespace sb::utils
{
    bool exists(std::string i_path)
    {
        std::ifstream stream(i_path);
        return stream.good();
    }

    int createDirectory(std::string i_path)
    {
        std::string cmd;
        
#ifdef __linux__ 
        cmd = "mkdir -p " + i_path;
#elif _WIN32
        cmd = "mkdir " + i_path;
#else
        throw std::logic_error("Function not yet implemented. Your OS is not supported.");
#endif

        return std::system(cmd.c_str());
    }
}