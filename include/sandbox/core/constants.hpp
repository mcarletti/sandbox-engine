/** @file constants.hpp
 *  @brief List of common mathematical and physical constants.
 * 
 *  All values have at most 8 decimals, which is the zero threshold.
 *  If needed, units are all according to the international system.
 * 
 *  @author Marco Carletti
*/
#pragma once

#include <sandbox/core/types.hpp>

namespace sb
{
    //! Epsilon. Used to define zero threshold.
    const real EPS = 1e-8;

    //! PI or golden ratio.
    const real PI =  3.14159265;

    //! Euler's number. Base of the natural logarith.
    const real E =  2.71828183;

    //! Golden ratio or "sectio aurea".
    const real PHI =  1.61803399;

    //! Degrees to radians conversion factor (PI/180).
    const real DEG2RAD =  0.01745329;

    //! Radians to degrees conversion factor (180/PI).
    const real RAD2DEG = 57.29577958;

    //! Earth average gravitational acceleration.
    const real GRAVITY =  9.80665;

    //! Universal gravitational constant in [m^3 / (Kg s^2)].
    const real G =  6.6743015e-11;

    //! Speed of light in vacuum in [m/s].
    const real C = 299792458;
}