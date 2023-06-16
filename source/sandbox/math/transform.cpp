#include <sandbox/math/transform.hpp>
#include <sandbox/math/Vector3.hpp>
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

                const Vector3 ax(axis.normalize());
                real x = ax.at(0);
                real y = ax.at(1);
                real z = ax.at(2);

                r(0,0) = c + x*x * (1.0 - c);
                r(0,1) = x*y * (1.0 - c) - z*s;
                r(0,2) = x*z * (1.0 - c) + y*s;

                r(1,0) = y*x * (1.0 - c) + z*s;
                r(1,1) = c + y*y * (1.0 - c);
                r(1,2) = y*z * (1.0 - c) - x*s;

                r(2,0) = z*x * (1.0 - c) - y*s;
                r(2,1) = z*y * (1.0 - c) + x*s;
                r(2,2) = c + z*z * (1.0 - c);

                r(3,3) = 1.0;

                break;
            }
        }

        return r * m;
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