#include <sandbox/utils/string.hpp>
#include <sstream>
#include <iomanip>
#include <cmath>

namespace sb::utils
{
    void trim(std::string &o_str)
    {
        o_str.erase(0, o_str.find_first_not_of(" \t\n"));
        o_str.erase(o_str.find_last_not_of(" \t\n") + 1);
    }

    std::string join(const std::vector<std::string> &i_strings, const std::string &i_connector)
    {
        if (i_strings.empty())
            return "";
        std::string str = "";
        for (uint i = 0; i < i_strings.size()-1; ++i)
            str += i_strings[i] + i_connector;
        str += i_strings[i_strings.size()-1];
        return str;
    }

    std::vector<std::string> split(const std::string &i_string, const std::string &i_separator)
    {
        std::vector<std::string> list;

        size_t from = 0;
        size_t to = i_string.find(i_separator, from);

        if (to == std::string::npos)
        {
            list.push_back(i_string);
            return list;
        }

        size_t nchars = 0;
        while (to != std::string::npos)
        {
            nchars = to - from;
            list.push_back( i_string.substr(from, nchars) );
            from = to + 1;
            if (from >= i_string.size())
                break;
            to = i_string.find(i_separator, from);
        }

        nchars = i_string.size() - from;
        std::string last = i_string.substr(from, nchars);
        if (!last.empty())
            list.push_back(last);

        return list;
    }

    int toInt(const std::string &i_str)
    {
        return (int)toFloat(i_str);
    }

    float toFloat(const std::string &i_str)
    {
        try
        {
            return std::atof(i_str.c_str());
        }
        catch(...)
        {
            return std::nanf("0");
        }
    }

    double toDouble(const std::string &i_str)
    {
        return (double)toFloat(i_str);
    }

    bool toBool(const std::string &i_str)
    {
        if (i_str == "0" || i_str == "false" || i_str == "False")
            return false;
        if (i_str == "1" || i_str == "true" || i_str == "True")
            return true;
        return true;
    }

    std::vector<int> toVeci(const std::string &i_str)
    {
        return toVec<int>(i_str);
    }

    std::vector<float> toVecf(const std::string &i_str)
    {
        return toVec<float>(i_str);
    }

    std::vector<double> toVecd(const std::string &i_str)
    {
        return toVec<double>(i_str);
    }

    std::string pad(int i_num, char c, uint i_len)
    {
        std::stringstream ss;
        ss << std::setfill(c) << std::setw(i_len) << i_num;
        return ss.str();
    }

    std::string pad(double i_num, char c, uint i_len, uint i_precision)
    {
        std::stringstream ss;
        ss << std::setfill(c) << std::setw(i_len) << std::fixed << std::setprecision(i_precision) << i_num;
        return ss.str();
    }
}