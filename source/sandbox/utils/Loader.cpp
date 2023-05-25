#include <sandbox/utils/Loader.hpp>
#include <sandbox/utils/Logger.hpp>
#include <sandbox/utils/string.hpp>
#include <fstream>
#include <stdexcept>

namespace sb::utils
{
    std::string Loader::readFileTXT(const std::string& filename)
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

    ConfigINI Loader::readFileINI(std::string& i_filename)
    {
        ConfigINI ini;

        std::ifstream stream(i_filename);
        if (!stream.is_open())
            throw std::logic_error("Cannot open file: " + i_filename);

        // aux variables
        std::string line;
        std::string param;
        std::string value;
        size_t pos;

        while (!stream.eof())
        {
            getline(stream, line);
            sb::utils::trim(line);

            // skip empty lines
            if (line.empty())
                continue;

            // skip comment lines
            if (line.at(0) == ';' || line.at(0) == '#')
                continue;

            // remove comments (if any)
            pos = line.find_first_of(";#");
            if (pos != std::string::npos)
                line = line.substr(0, pos);

            // find separator between key and value
            pos = line.find('=');
            if (pos == std::string::npos)
                throw std::logic_error("Invalid line: " + line);
            
            // prepare key and value
            param = line.substr(0, pos);
            value = line.substr(pos+1, line.size());
            sb::utils::trim(param);
            sb::utils::trim(value);

            // save variable
            ini[param] = value;
        }

        return ini;
    }
}