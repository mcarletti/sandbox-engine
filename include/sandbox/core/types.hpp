/** @file types.hpp
 *  @brief List of Sandbox Engine custom types, aliases and structures.
 * 
 *  @author Marco Carletti
*/
#pragma once

namespace sb
{
    using uint  = unsigned int;
    using ulong = unsigned long;
    using uchar = unsigned char;
    using byte  = uchar;

#ifdef __DOUBLE_PRECISION
    using real = double;
    const real SB_REAL_MIN = __DBL_MIN__;
    const real SB_REAL_MAX = __DBL_MAX__;
#else
    using real = float;
    const real SB_REAL_MIN = __FLT_MIN__;
    const real SB_REAL_MAX = __FLT_MAX__;
#endif
}