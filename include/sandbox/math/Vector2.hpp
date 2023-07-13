/** @file Vector2.hpp
 *  @brief 2-dimensional vector class.
 * 
 *  @author Marco Carletti
*/
#pragma once

#include <sandbox/math/Vector.hpp>

namespace sb
{
    class Vector2 : public Vector
    {
    public:

        /*!
            @brief Constructor.

            Allocate a vector of two real numbers.
            Elements are set to 0.
        */
        Vector2();

        /*!
            @brief Constructor.

            @param v Standard vector of real numbers. Size must be 2.
        */
        Vector2(const std::vector<real>& v);

        /*!
            @brief Constructor. Initializes a Vector from braced-init-list.

            @param list Non empty list of real numbers.
        */
        Vector2(const std::initializer_list<real>& list);

        //! Copy constructor from parent class.
        Vector2(const Vector& v);

        //! Copy constructor.
        Vector2(const Vector2& v);

        //! Destructor.
        ~Vector2();
    };
}