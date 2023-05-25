/** @file Loader.hpp
 *  @brief Core utility to load assets.
 * 
 *  @author Marco Carletti
*/
#pragma once

#include <string>
#include <map>

namespace sb::utils
{
    //! Configuration file alias: primary key is the section string identifier, secondary is the variable name.
    using ConfigINI = std::map< std::string, std::string>;

    class Loader
    {
    public:

        /*!
            @brief Load a text file, line by line.

            @param filename Path to the text file to read.
            @return File content as string. Lines are separated by '\n' character.
        */
        static std::string readFileTXT(const std::string& filename);

        /*!
            @brief Load a ini configuration file.

            @param filename Path to the config file to read.
            @return File content as a map of variables organized in sections.
        */
        static ConfigINI readFileINI(std::string& i_filename);
    };
}