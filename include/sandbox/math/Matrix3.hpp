/** @file Matrix3.hpp
 *  @brief 3x3 matrix class.
 * 
 *  @author Marco Carletti
*/
#pragma once

#include <sandbox/math/Matrix.hpp>

namespace sb
{
    class Matrix3 : public Matrix
    {
    public:

        /*!
            @brief Constructor.

            Allocate a 3x3 identity matrix of real numbers.
        */
        Matrix3();

        /*!
            @brief Constructor.

            @param v Standard vector of real numbers. Size must be 9.
        */
        Matrix3(const std::vector<real>& v);

        //! Copy constructor from parent class.
        Matrix3(const Matrix& m);

        //! Copy constructor.
        Matrix3(const Matrix3& m);

        //! Destructor.
        ~Matrix3();
    };
}