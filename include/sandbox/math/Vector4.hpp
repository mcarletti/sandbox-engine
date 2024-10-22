/** @file Vector4.hpp
 *  @brief 4-dimensional vector class.
 * 
 *  @author Marco Carletti
*/
#pragma once

#include <sandbox/math/Vector.hpp>

namespace sb
{
    class Vector4 : public Vector
    {
    public:

        /*!
            @brief Constructor.

            Allocate a vector of four real numbers.
            Elements are set to 0.
        */
        Vector4();

        /*!
            @brief Constructor.

            @param v Standard vector of real numbers. Size must be 4.
        */
        Vector4(const std::vector<real>& v);

        /*!
            @brief Constructor. Initializes a Vector from braced-init-list.

            @param list Non empty list of real numbers.
        */
        Vector4(const std::initializer_list<real>& list);

        //! Copy constructor from parent class.
        Vector4(const Vector& v);

        //! Copy constructor.
        Vector4(const Vector4& v);

        //! Destructor.
        ~Vector4();
    };
}