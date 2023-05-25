/** @file string.hpp
 *  @brief Set of static functions for string management and conversion.
 * 
 *  @author Marco Carletti
*/
#pragma once

#include <string>
#include <vector>

namespace sb::utils
{
    // string management
    void trim(std::string &o_str);
    std::string join(const std::vector<std::string>& i_strings, const std::string &i_connector = "");
    std::vector<std::string> split(const std::string &i_str, const std::string &i_separator = " ");

    // conversion
    int toInt(const std::string &i_str);
    float toFloat(const std::string &i_str);
    double toDouble(const std::string &i_str);
    bool toBool(const std::string &i_str);

    template <class T>
    std::vector<T> toVec(const std::string &i_str)
    {
        std::vector<T> vec;
        for (const std::string &s : split(i_str))
            vec.push_back((T)toFloat(s));
        return vec;
    }

    std::vector<int> toVeci(const std::string &i_str);
    std::vector<float> toVecf(const std::string &i_str);
    std::vector<double> toVecd(const std::string &i_str);

    // print
    std::string pad(int i_num, char p = '0', uint i_len = 4);
    std::string pad(double i_num, char p = '0', uint i_len = 8, uint i_precision = 2);
}