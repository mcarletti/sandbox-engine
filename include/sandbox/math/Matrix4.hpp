/** @file Matrix4.hpp
 *  @brief 4x4 matrix class.
 * 
 *  @author Marco Carletti
*/
#pragma once

#include <sandbox/math/Matrix.hpp>

namespace sb
{
    class Matrix4 : public Matrix
    {
    public:

        /*!
            @brief Constructor.

            Allocate a 4x4 identity matrix of real numbers.
        */
        Matrix4();

        /*!
            @brief Constructor.

            @param v Standard vector of real numbers. Size must be 16.
        */
        Matrix4(const std::vector<real>& v);

        //! Copy constructor from parent class.
        Matrix4(const Matrix& m);

        //! Copy constructor.
        Matrix4(const Matrix4& m);

        //! Destructor.
        ~Matrix4();
    };
}