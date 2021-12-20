#include <sandbox/utils/Loader.hpp>
#include <sandbox/utils/Logger.hpp>
#include <fstream>

namespace sb
{
    std::string Loader::readTextFile(const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
        {
            Logger::write("Unable to open file: " + filename);
            return "";
        }

        std::string text("");
        std::string line("");

        while (getline(file, line))
            text += line + '\n';
        
        file.close();

        return text;
    }
}