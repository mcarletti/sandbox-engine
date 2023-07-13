#include <sandbox/math/transform.hpp>
#include <sandbox/math/Vector3.hpp>
#include <sandbox/math/Matrix.hpp>
#include <cmath>
#include <cassert>
#include <iostream>

namespace sb
{
    Matrix translate(const Matrix& m, const Vector& v)
    {
        const uint size = v.size();
        assert(size == 2 || size == 3);
        assert(m.rows() == m.cols());
        assert(m.rows() == size + 1);

        Matrix res(m);
        for (uint i = 0; i < size; ++i)
            res(i, size) += v.at(i);

        return res;
    }

    Matrix rotate(const Matrix& m, const real angle, const Vector& axis)
    {
        assert(m.rows() == m.cols());
        assert(m.rows() == 3 || m.rows() == 4);

        const real c = cos(angle);
        const real s = sin(angle);

        Matrix r(m.rows(), m.cols());

        switch (m.rows())
        {
            case 3:
            {
                r(0,0) = c;
                r(0,1) = -s;

                r(1,0) = s;
                r(1,1) = c;

                r(2,2) = 1.0;

                break;
            }
            case 4:
            {
                assert(axis.size() == 3);

                const Vector3 nax = Vector::normalize(axis);
                const Vector3 tmp = nax * ((real)1. - c);

                const real ax = nax.at(0);
                const real ay = nax.at(1);
                const real az = nax.at(2);

                const real tx = tmp.at(0);
                const real ty = tmp.at(1);
                const real tz = tmp.at(2);

                r(0,0) = c + tx * ax;
                r(0,1) = tx * ay + s * az;
                r(0,2) = tx * az - s * ay;

                r(1,0) = ty * ax - s * az;
                r(1,1) = c + ty * ay;
                r(1,2) = ty * az + s * ax;

                r(2,0) = tz * ax + s * ay;
                r(2,1) = tz * ay - s * ax;
                r(2,2) = c + tz * az;

                r(3,3) = (real)1.0;

                break;
            }
        }

        return r.matmul(m);
    }

    Vector rotate(const Vector& v, const real angle, const Vector& axis)
    {
        const uint size = v.size();
        assert(size == 2 || size == 3);

        Matrix m = Matrix::identity(size + 1);
        for (uint i = 0; i < size; ++i)
            m(i, size) = v.at(i);

        m = rotate(m, angle, axis);
        Vector hres = m.col(size);
        Vector res(size);
        for (uint i = 0; i < size; ++i)
            res[i] = hres.at(i);

        return res;
    }

    Matrix scale(const Matrix& m, const real s)
    {
        assert(m.rows() == m.cols());
        assert(m.rows() == 3 || m.rows() == 4);

        Matrix res(m);
        for (uint i = 0; i < m.rows() - 1; ++i)
            res(i, i) *= s;

        return res;
    }

    Matrix scale(const Matrix& m, const Vector& v)
    {
        const uint size = v.size();
        assert(size == 2 || size == 3);
        assert(m.rows() == m.cols());
        assert(m.rows() == size + 1);

        Matrix res(m);
        for (uint i = 0; i < size; ++i)
            res(i, i) *= v.at(i);

        return res;
    }
}