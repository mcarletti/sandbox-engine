/** @file transform.hpp
 *  @brief Cartesian space transformation utilities.
 * 
 *  @author Marco Carletti
*/
#pragma once

#include <sandbox/math/Vector.hpp>
#include <sandbox/math/Matrix.hpp>

namespace sb
{
    /*!
        @brief Translate a matrix by a vector.

        @param m The matrix to translate.
        @param v The translation vector.
    */
    Matrix translate(const Matrix& m, const Vector& v);

    /*!
        @brief Rotate a 2D or 3D matrix by an angle around an axis.

        @param m The matrix to rotate.
        @param angle The angle in radians.
        @param v The rotation axis (ignored for 2D rotation).
    */
    Matrix rotate(const Matrix& m, const real angle, const Vector& axis);

    /*!
        @brief Scale a matrix by a scalar.

        @param m The matrix to scale.
        @param s The scale factor.
    */
    Matrix scale(const Matrix& m, const real s);

    /*!
        @brief Scale a matrix by a vector.

        @param m The matrix to scale.
        @param v The scale vector.
    */
    Matrix scale(const Matrix& m, const Vector& v);
}