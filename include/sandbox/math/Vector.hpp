/** @file Vector.hpp
 *  @brief N-dimensional vector class.
 * 
 *  @author Marco Carletti
*/
#pragma once

#include <sandbox/core/types.hpp>
#include <vector>

namespace sb
{
    class Vector
    {
    public:

        /*!
            @brief Constructor.

            Allocate a vector of real numbers.
            Elements are set to 0.

            @param size The number of elements the vector will store. It must be grater than 0.
        */
        Vector(const uint size);

        /*!
            @brief Constructor.

            @param v Standard vector of real numbers. Size must be greather than 0.
        */
        Vector(const std::vector<real>& v);

        /*!
            @brief Constructor. Initializes a Vector from braced-init-list.

            @param list Non empty list of real numbers.
        */
        Vector(const std::initializer_list<real>& list);

        //! Copy constructor.
        Vector(const Vector& v);

        //! Destructor.
        ~Vector();

        //! Get data pointer.
        const real* data() const;

        /*! 
            @brief Get the number of elements.

            @return Number of vector elements.
        */
        uint size() const;

        /*!
            @brief Get a reference to the i-th element.

            @param i Index of the element. It must be between 0 and the vector size.
            @return A reference to the i-th element.
        */
        real& operator[](const uint i);

        /*!
            @brief Get a reference to the i-th element.

            @param i Index of the element. It must be between 0 and the vector size.
            @return A reference to the i-th element.
        */
        real& operator()(const uint i);

        /*!
            @brief Get a copy of the i-th element.

            @param i Index of the element. It must be between 0 and the vector size.
            @return A copy of the i-th element.
        */
        real at(const uint i) const;

        /*! 
            @brief Compute the L2 norm of the vector.

            @return Length of the vector as L2 norm.
        */
        real norm() const;

        //! Return normalized vector (ie. values are scaled between 0 and 1).
        Vector normalize() const;

        /*!
            @brief Compute the dot product with the input vector.

            @param v Vector of the same size of the caller.
            @return Dot product as scalar (real).
        */
        real dot(const Vector& v) const;

        /*!
            @brief Compute the angle with input vectors.

            @param v Vector of the same size of the caller.
            @return Angle between the vectors in radians.
        */
        real angle(const Vector& v) const;

        /*!
            @brief Compute the cross product with the input vector.

            Vectors must contain 3 elements.

            @param v Vector of size 3 to compute the product.
            @return Cross product as a vector.
        */
        Vector cross(const Vector& v) const;

        //! Vector per-value comparison.
        bool operator==(const Vector& v) const;

        //! Assignment operator.
        void operator=(const Vector& v);

        //! Add a scalar to the vector elements.
        Vector operator+(const real& v) const;

        //! Add a scalar to the vector elements (inplace).
        void operator+=(const real& v);

        //! Subtract a scalar to the vector elements.
        Vector operator-(const real& v) const;

        //! Subtract a scalar to the vector elements (inplace).
        void operator-=(const real& v);

        //! Negate vector.
        Vector operator-() const;

        //! Multiply each element by a scalar.
        Vector operator*(const real& v) const;

        //! Multiply each element by a scalar (inplace).
        void operator*=(const real& v);

        //! Divide each element by a non-zero scalar.
        Vector operator/(const real& v) const;

        //! Divide each element by a non-zero scalar (inplace).
        void operator/=(const real& v);

        //! Add two vectors element-wise.
        Vector operator+(const Vector& v) const;

        //! Add two vectors element-wise (inplace).
        void operator+=(const Vector& v);

        //! Subtract two vectors element-wise.
        Vector operator-(const Vector& v) const;

        //! Subtract two vectors element-wise (inplace).
        void operator-=(const Vector& v);

        //! Multiply two vectors element-wise.
        Vector operator*(const Vector& v) const;

        //! Multiply two vectors element-wise (inplace).
        void operator*=(const Vector& v);

        //! Divide two vectors element-wise.
        Vector operator/(const Vector& v) const;

        //! Divide two vectors element-wise (inplace).
        void operator/=(const Vector& v);

    protected:

        //! Constructor.
        Vector() = default;

        //! Data pointer.
        real* _data{nullptr};

        //! Size of the vector.
        uint _size{0};
    };
}