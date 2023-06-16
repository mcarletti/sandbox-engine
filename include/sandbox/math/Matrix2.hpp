/** @file Matrix2.hpp
 *  @brief 2x2 matrix class.
 * 
 *  @author Marco Carletti
*/
#pragma once

#include <sandbox/math/Matrix.hpp>

namespace sb
{
    class Matrix2 : public Matrix
    {
    public:

        /*!
            @brief Constructor.

            Allocate a 2x2 identity matrix of real numbers.
        */
        Matrix2();

        /*!
            @brief Constructor.

            @param v Standard vector of real numbers. Size must be 2.
        */
        Matrix2(const std::vector<real>& v);

        //! Copy constructor from parent class.
        Matrix2(const Matrix& m);

        //! Copy constructor.
        Matrix2(const Matrix2& m);

        //! Destructor.
        ~Matrix2();
    };
}