/** @file Matrix.hpp
 *  @brief MxN matrix class.
 * 
 *  @author Marco Carletti
*/
#pragma once

#include <sandbox/math/Vector.hpp>
#include <sstream>

namespace sb
{
    class Matrix
    {
    public:

        /*!
            @brief Constructor.

            Allocate a matrix of real numbers.
            Elements are set to 0.

            @param rows The number of rows of the matrix. It must be grater than 0.
            @param cols The number of rows of the matrix. It must be grater than 0.
        */
        Matrix(const uint rows, const uint cols);

        /*!
            @brief Constructor.

            Vector data is reshaped to a rows by cols matrix.
            Shapes must match. If rows and cols are equal to 0 (one or both), it is assumed
            the vector could be shaped into a square matrix (row major).

            @param v Standard vector of real numbers that will be reshaped to a rows by cols matrix.
            @param rows The number of rows of the matrix.
            @param cols The number of rows of the matrix.
        */
        Matrix(const std::vector<real>& v, const uint rows = 0, const uint cols = 0);

        //! Copy constructor.
        Matrix(const Matrix& m);

        //! Destructor.
        ~Matrix();

        //! Constructor of the identity matrix.
        static Matrix identity(const uint size);

        //! String representation of the matrix.
        std::string toString() const;

        //! Get data pointer.
        const real* data() const;

        //! Return number of rows.
        uint rows() const;

        //! Return number of columns.
        uint cols() const;

        //! Return number of elements (rows * cols).
        uint size() const;

        //! Return the matrix diagonal as a vector.
        Vector diag() const;

        /*!
            @brief Get a copy of the i-th row.

            @param i Index of the row. It must be between 0 and number of rows.
            @return A copy to the i-th row.
        */
        Vector row(const uint i) const;

        /*!
            @brief Get a copy of the i-th column.

            @param i Index of the column. It must be between 0 and number of columns.
            @return A copy to the i-th column.
        */
        Vector col(const uint i) const;

        /*!
            @brief Get a reference to the i-th element, selected row major.

            @param i Index of the element. It must be between 0 and the matrix total size.
            @return A reference to the i-th element.
        */
        real& operator[](const uint i);

        /*!
            @brief Get a reference to the ij-th element.

            @param i Row index of the element. It must be between 0 and the matrix row size.
            @param j Col index of the element. It must be between 0 and the matrix column size.
            @return A reference to the ij-th element.
        */
        real& operator()(const uint i, const uint j);

        /*!
            @brief Get a copy to the i-th element, selected row major.

            @param i Index of the element. It must be between 0 and the matrix total size.
            @return A copy of the i-th element.
        */
        real at(const uint i) const;

        /*!
            @brief Get a copy of the ij-th element.

            @param i Row index of the element. It must be between 0 and the matrix row size.
            @param j Col index of the element. It must be between 0 and the matrix column size.
            @return A copy to the ij-th element.
        */
        real at(const uint i, const uint j) const;

        /*!
            @brief Get a copy of the submatrix of size (rows, cols) which starts from ij-th element.

            @param i Row index of the top-left corner of the submatrix.
            @param j Col index of the top-left corner of the submatrix.
            @param rows Row size of the submatrix.
            @param cols Col size of the submatrix.
            @return The submatrix.
        */
        Matrix get(const uint i, const uint j, const uint rows, const uint cols) const;

        /*!
            @brief Sparse update of matrix values.

            @param indices Elements to be updated, row major.
            @param value New value, equal for all indices.
        */
        void set(const std::vector<uint>& indices, real value);

        /*!
            @brief Sparse update of matrix values.

            @param indices Elements to be updated, row major.
            @param values New values relative to indices.
        */
        void set(const std::vector<uint>& indices, const std::vector<real>& values);

        /*!
            @brief Update sub-matrix.

            @param i Row index of the top-left corner of the submatrix.
            @param j Col index of the top-left corner of the submatrix.
            @param m Matrix of new values.
        */
        void set(const uint i, const uint j, const Matrix& m);

        //! Matrix per-value comparison.
        bool operator==(const Matrix& m) const;

        //! Assignment operator.
        void operator=(const Matrix& m);

        //! Add a scalar to the Matrix elements.
        Matrix operator+(const real& v) const;

        //! Add a scalar to the Matrix elements (inplace).
        void operator+=(const real& v);

        //! Subtract a scalar to the Matrix elements.
        Matrix operator-(const real& v) const;

        //! Subtract a scalar to the Matrix elements (inplace).
        void operator-=(const real& v);

        //! Negate vector.
        Matrix operator-() const;

        //! Multiply each element by a scalar.
        Matrix operator*(const real& v) const;

        //! Multiply each element by a scalar (inplace).
        void operator*=(const real& v);

        //! Divide each element by a non-zero scalar.
        Matrix operator/(const real& v) const;

        //! Divide each element by a non-zero scalar (inplace).
        void operator/=(const real& v);

        //! Add two matrices element-wise.
        Matrix operator+(const Matrix& m) const;

        //! Add two matrices element-wise (inplace).
        void operator+=(const Matrix& m);

        //! Subtract two matrices element-wise.
        Matrix operator-(const Matrix& m) const;

        //! Subtract two matrices element-wise (inplace).
        void operator-=(const Matrix& m);

        //! Multiply two matrices element-wise.
        Matrix operator*(const Matrix& m) const;

        //! Multiply two matrices element-wise (inplace).
        void operator*=(const Matrix& m);

        //! Divide two matrices element-wise.
        Matrix operator/(const Matrix& m) const;

        //! Divide two matrices element-wise (inplace).
        void operator/=(const Matrix& m);

        //! Matrix multiplication.
        Matrix matmul(const Matrix& m) const;

        //! Compute the trace (ie. sum of diagonal values).
        real trace() const;

        //! Transpose the matrix.
        Matrix t() const;

        //! Compute the determinant.
        real det() const;

        //! Compute the inverse matrix.
        Matrix inv() const;

        //! Translate the matrix by a vector (inplace).
        void translate(const Vector& v);

        //! Scale matrix (inplace).
        void scale(const real& v);

        //! Scale matrix axes independently (inplace).
        void scale(const Vector& v);

    protected:

        //! Constructor.
        Matrix() = default;

        /*!
            @brief Compute matrix of cofactors relative to the row-col anchor value of a NxN matrix.

            Output cofactor matrix is a NxN where only the submatrix nxn is populated with the cofactors.
            This function is used to compute the determinant of the former matrix and the output cofactor
            matrix is used to save memory and store the temporary cofactors during determinant computation.

            @param cfs Reference to the output matrix of cofactors.
            @param row Current anchor row to be skipped.
            @param col Current anchor row to be skipped.
            @param n Dimension of the square submatrix of cfs used to store the cofactors.
        */
        void cofactors(Matrix& cfs, const uint row, const uint col, const uint n) const;

        /*!
            @brief Compute the conjugate matrix.
            
            @param adj Output matrix of conjugate values.
        */
        void adjoint(Matrix& adj) const;

        /*!
            @brief Compute the determinant of square submatrix nxn.
            
            @param n Order (size) of the submatrix.
        */
        real det(const uint n) const;

        //! Data pointer.
        real* _data{nullptr};

        //! Number of rows of the matrix.
        uint _rows{0};

        //! Number of columns of the matrix.
        uint _cols{0};

        //! Number of elements of the matrix.
        uint _size{0};
    };
}
