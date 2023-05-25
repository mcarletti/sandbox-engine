/** @file filesystem.hpp
 *  @brief Access OS specific functions to manage file system.
 * 
 *  @author Marco Carletti
*/
#pragma once

#include <string>

namespace sb::utils
{
    /*!
        @brief Check whether a file path exists.

        @param filename Path to the file or directory.
        @return State of existence of the input path.
    */
    bool exists(std::string i_path);

    /*!
        @brief Create a new directory and it parent tree, if needed.

        @param filename Path of the new folder.
        @return Output state of the folder creation command according to OS.
    */
    int createDirectory(std::string i_path);
}