/** @file Loader.hpp
 *  @brief Core utility to load assets.
 * 
 *  @author Marco Carletti
*/
#pragma once

#include <string>

namespace sb
{
    class Loader
    {
    public:

        /*!
            @brief Load a text file, line by line.

            @param filename Enable/disable append mode.
            @return File content as string. Lines are separated by '\n' character.
        */
        static std::string readTextFile(const std::string& filename);
    };
}