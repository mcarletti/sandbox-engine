#include <sandbox/core/constants.hpp>
#include <sandbox/math/Matrix.hpp>
#include <sandbox/math/Vector.hpp>
#include <cmath>
#include <cstring>
#include <cassert>

namespace sb
{
    Matrix::Matrix(const uint rows, const uint cols)
    {
        assert(rows > 0);
        assert(cols > 0);

        _size = rows * cols;
        _rows = rows;
        _cols = cols;

        _data = new real[_size];

        memset(_data, 0, _size * sizeof(real));
    }

    Matrix::Matrix(const std::vector<real>& v, const uint rows, const uint cols)
    {
        if (rows * cols > 0)
        {
            assert(rows > 0);
            assert(cols > 0);

            _size = rows * cols;
            _rows = rows;
            _cols = cols;
        }
        else
        {
            const uint n = std::sqrt(v.size());
            assert (v.size() == n * n);

            _size = n * n;
            _rows = n;
            _cols = n;
        }

        _data = new real[_size];

        memcpy(_data, v.data(), v.size() * sizeof(real));
    }

    Matrix::Matrix(const Matrix& m)
    {
        _size = m._rows * m._cols;
        _rows = m._rows;
        _cols = m._cols;

        _data = new real[m._rows * m._cols];

        memcpy(_data, m._data, _size * sizeof(real));
    }

    Matrix::~Matrix()
    {
        if (_data != nullptr)
        {
            delete _data;
            _data = nullptr;
        }

        _size = 0;
        _rows = 0;
        _cols = 0;
    }

    Matrix Matrix::identity(const uint rows, const uint cols)
    {
        Matrix m(rows, cols);
        const uint size = std::min(rows, cols);
        for (uint i = 0; i < size; ++i)
            m(i, i) = 1;
        return m;
    }

    Vector Matrix::diag() const
    {
        const uint n = std::min(_rows, _cols);
        Vector d(n);
        for (uint i = 0; i < n; ++i)
            d[i] = _data[_rows * i + i];
        return d;
    }

    const real* Matrix::data() const
    {
        return _data;
    }

    uint Matrix::rows() const
    {
        return _rows;
    }

    uint Matrix::cols() const
    {
        return _cols;
    }

    uint Matrix::size() const
    {
        return _size;
    }

    Vector Matrix::row(const uint i) const
    {
        assert(i < _rows);

        Vector row(_cols);
        for (uint j = 0; j < _cols; ++j)
            row[j] = _data[_rows * i + j];
        return row;
    }

    Vector Matrix::col(const uint i) const
    {
        assert(i < _cols);

        Vector col(_rows);
        for (uint j = 0; j < _rows; ++j)
            col[j] = _data[_rows * j + i];
        return col;
    }

    real& Matrix::operator[](const uint i)
    {
        assert(i < _size);
        return _data[i];
    }

    real& Matrix::operator()(const uint i, const uint j)
    {
        assert(i < _rows);
        assert(j < _cols);

        return _data[_rows * i + j];
    }

    real Matrix::at(const uint i) const
    {
        assert(i < _size);
        return _data[i];
    }

    real Matrix::at(const uint i, const uint j) const
    {
        assert(i < _rows);
        assert(j < _cols);

        return _data[_rows * i + j];
    }

    Matrix Matrix::get(const uint i, const uint j, const uint rows, const uint cols) const
    {
        assert(rows > 0);
        assert(cols > 0);
        assert(i + rows < _cols);
        assert(j + cols < _cols);

        Matrix res(rows, cols);

        for (uint v = i; v < rows; ++v)
            for (uint u = j; u < cols; ++u)
                res(v, u) = _data[_rows * v + u];
        
        return res;
    }

    void Matrix::set(const std::vector<uint>& indices, real value)
    {
        for (auto& i : indices)
        {
            assert(i < _size);
            _data[i] = value;
        }
    }

    void Matrix::set(const std::vector<uint>& indices, const std::vector<real>& values)
    {
        assert(indices.size() == values.size());

        for (uint i = 0; i < indices.size(); ++i)
        {
            assert(indices[i] < _size);
            _data[i] = values[i];
        }
    }

    void Matrix::set(const uint i, const uint j, const Matrix& m)
    {
        assert(i < _rows && j < _cols);
        assert(i + m._rows <= _rows);
        assert(j + m._cols <= _cols);

        uint max_row = i + m._rows;
        uint max_col = j + m._cols;
        uint count = 0;

        for (uint r = i; r < max_row; ++r)
            for (uint c = j; c < max_col; ++c)
                _data[r * _rows + c] = m._data[count++];
    }

    bool Matrix::operator==(const Matrix& m) const
    {
        assert(_rows == m._rows);
        assert(_cols == m._cols);

        bool res = true;

        for (uint i = 0; i < _size; ++i)
            res &= _data[i] == m._data[i];

        return res;
    }

    void Matrix::operator=(const Matrix& m)
    {
        assert(_rows == m._rows);
        assert(_cols == m._cols);
        memcpy(_data, m._data, _size * sizeof(real));
    }

    Matrix Matrix::operator+(const real& v) const
    {
        Matrix res(_rows, _cols);
        for (uint i = 0; i < _size; ++i)
            res._data[i] = _data[i] + v;
        return res;
    }

    void Matrix::operator+=(const real& v)
    {
        for (uint i = 0; i < _size; ++i)
            _data[i] += v;
    }

    Matrix Matrix::operator-(const real& v) const
    {
        Matrix res(_rows, _cols);
        for (uint i = 0; i < _size; ++i)
            res._data[i] = _data[i] - v;
        return res;
    }

    void Matrix::operator-=(const real& v)
    {
        for (uint i = 0; i < _size; ++i)
            _data[i] -= v;
    }

    void Matrix::operator-=(const Matrix& m)
    {
        assert(_rows == m._rows);
        assert(_cols == m._cols);

        for (uint i = 0; i < _size; ++i)
            _data[i] -= m._data[i];
    }

    Matrix Matrix::operator*(const real& v) const
    {
        Matrix res(_rows, _cols);
        for (uint i = 0; i < _size; ++i)
            res._data[i] = _data[i] * v;
        return res;
    }

    void Matrix::operator*=(const real& v)
    {
        for (uint i = 0; i < _size; ++i)
            _data[i] *= v;
    }

    Matrix Matrix::operator/(const real& v) const
    {
        assert(std::abs(v) >= EPS);

        Matrix res(_rows, _cols);
        for (uint i = 0; i < _size; ++i)
            res._data[i] = _data[i] / v;
        return res;
    }

    void Matrix::operator/=(const real& v)
    {
        assert(std::abs(v) >= EPS);

        for (uint i = 0; i < _size; ++i)
            _data[i] /= v;
    }

    Matrix Matrix::operator+(const Matrix& m) const
    {
        assert(_rows == m._rows);
        assert(_cols == m._cols);

        Matrix res(_rows, _cols);
        for (uint i = 0; i < _size; ++i)
            res._data[i] = _data[i] + m._data[i];
        return res;
    }

    void Matrix::operator+=(const Matrix& m)
    {
        assert(_rows == m._rows);
        assert(_cols == m._cols);

        for (uint i = 0; i < _size; ++i)
            _data[i] += m._data[i];
    }

    Matrix Matrix::operator-(const Matrix& m) const
    {
        assert(_rows == m._rows);
        assert(_cols == m._cols);

        Matrix res(_rows, _cols);
        for (uint i = 0; i < _size; ++i)
            res._data[i] = _data[i] - m._data[i];
        return res;
    }

    Matrix Matrix::operator-() const
    {
        Matrix res(_rows, _cols);

        for (uint i = 0; i < _size; ++i)
            res._data[i] = -_data[i];
        
        return res;
    }

    Matrix Matrix::operator*(const Matrix& m) const
    {
        assert(_rows == m._rows);
        assert(_cols == m._cols);

        Matrix res(_rows, _cols);
        for (uint i = 0; i < _size; ++i)
            res._data[i] = _data[i] * m._data[i];
        return res;
    }

    void Matrix::operator*=(const Matrix& m)
    {
        assert(_rows == m._rows);
        assert(_cols == m._cols);

        for (uint i = 0; i < _size; ++i)
            _data[i] *= m._data[i];
    }

    Matrix Matrix::operator/(const Matrix& m) const
    {
        assert(_rows == m._rows);
        assert(_cols == m._cols);

        Matrix res(_rows, _cols);
        for (uint i = 0; i < _size; ++i)
            res._data[i] = _data[i] / m._data[i];
        return res;
    }

    void Matrix::operator/=(const Matrix& m)
    {
        assert(_rows == m._rows);
        assert(_cols == m._cols);

        for (uint i = 0; i < _size; ++i)
            _data[i] /= m._data[i];
    }

    Matrix Matrix::matmul(const Matrix& m) const
    {
        assert(_cols == m._rows);

        Matrix res(_rows, m._cols);

        for (uint i = 0; i < _rows; ++i)
        {
            for (uint j = 0; j < m._cols; ++j)
            {
                Vector&& v1 = row(i);
                Vector&& v2 = m.col(j);
                res(i, j) = v1.dot(v2);
            }
        }

        return res;
    }

    real Matrix::trace() const
    {
        const uint n = std::min(_rows, _cols);
        real t = 0.;
        for (uint i = 0; i < n; ++i)
            t += _data[_rows * i + i];
        return t;
    }

    Matrix Matrix::t() const
    {
        Matrix res(_cols, _rows);
        for (uint i = 0; i < _rows; ++i)
            for (uint j = 0; j < _cols; ++j)
                res._data[_cols * j + i] = _data[_rows * i + j];
        return res;
    }

    void Matrix::cofactors(Matrix& cfs, const uint row, const uint col, const uint n) const
    {
        uint i = 0, j = 0;
    
        for (uint r = 0; r < n; ++r)
        {
            for (uint c = 0; c < n; ++c) 
            {
                //  copying into temporary matrix only those
                //  element which are not in given row and column
                if (row != r && col != c) 
                {
                    cfs(i, j++) = this->at(r, c);
    
                    // row is filled, so increase row index and reset col index
                    if (j == n - 1) 
                    {
                        j = 0;
                        i++;
                    }
                }
            }
        }
    }

    void Matrix::adjoint(Matrix& adj) const
    {
        const uint n = _rows;

        if (n == 1)
        {
            adj(0, 0) = 1;
            return;
        }

        Matrix tmp(n, n);

        for (uint i = 0; i < n; ++i)
        {
            for (uint j = 0; j < n; ++j)
            {
                cofactors(tmp, i, j, n);

                // interchanging rows and columns to get the
                // transpose of the cofactor matrix
                adj(j, i) = (((i + j) % 2 == 0) ? 1 : -1) * (tmp.det(n - 1));
            }
        }
    }

    real Matrix::det() const
    {
        assert(_rows == _cols);
        const uint n = _rows;

        return det(n);
    }

    real Matrix::det(const uint n) const
    {
        const uint N = _rows;
        real d = 0.;

        if (n == 1)
            d = _data[0];
        else
        {
            Matrix tmp(N, N);

            // iterate for each element of first row
            for (uint i = 0; i < n; ++i) 
            {
                // get cofactor of mat[0][i]
                // always exclude first row and i-th column
                cofactors(tmp, 0, i, n);
                d += (i % 2 == 0 ? 1 : -1) * at(0, i) * tmp.det(n - 1);
            }
        }

        return d;
    }

    Matrix Matrix::inv() const
    {
        // source
        // https://www.geeksforgeeks.org/adjoint-inverse-matrix/

        assert(_rows == _cols);

        real d = det();
        assert(d > EPS);

        const uint n = _rows;

        Matrix adj(n, n);
        adjoint(adj);

        Matrix inverse(n, n);
        for (uint i = 0; i < n; ++i)
            for (uint j = 0; j < n; ++j)
                inverse(i, j) = adj(i, j) / d;

        return inverse;
    }
}