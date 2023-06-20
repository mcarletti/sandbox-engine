/** @file Vector3.hpp
 *  @brief 3-dimensional vector class.
 * 
 *  @author Marco Carletti
*/
#pragma once

#include <sandbox/math/Vector.hpp>

namespace sb
{
    class Vector3 : public Vector
    {
    public:

        /*!
            @brief Constructor.

            Allocate a vector of three real numbers.
            Elements are set to 0.
        */
        Vector3();

        /*!
            @brief Constructor.

            @param v Standard vector of real numbers. Size must be 3.
        */
        Vector3(const std::vector<real>& v);

        /*!
            @brief Constructor. Initializes a Vector from braced-init-list.

            @param list Non empty list of real numbers.
        */
        Vector3(const std::initializer_list<real>& list);

        //! Copy constructor from parent class.
        Vector3(const Vector& v);

        //! Copy constructor.
        Vector3(const Vector3& v);

        //! Destructor.
        ~Vector3();

        // aliases

        real& x{_data[0]};
        real& y{_data[1]};
        real& z{_data[2]};
    };
}