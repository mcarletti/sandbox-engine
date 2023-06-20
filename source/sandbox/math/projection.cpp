#include <sandbox/math/projection.hpp>
#include <sandbox/core/constants.hpp>
#include <cmath>
#include <cassert>

namespace sb
{
    Matrix4 ortho(const real left, const real right, const real bottom, const real top, const real near, const real far)
    {
        Matrix4 m;

        m(0,0) = 2.0 / (right - left);
        m(1,1) = 2.0 / (top - bottom);
        m(2,2) = 2.0 / (near - far);

        m(0,3) = - (right + left) / (right - left);
        m(1,3) = - (top + bottom) / (top - bottom);
        m(2,3) = - (far + near) / (far - near);

        return m;
    }

    Matrix4 perspective(const real fov, const real aspect, const real near, const real far)
    {
        assert(fov > EPS);
        assert(aspect > EPS);
        assert(near >= 0);
        assert((far - near) > EPS);

        const real tanHalfFov = tan(fov * 0.5);

        Matrix4 m;

        m(0,0) = 1.0 / (aspect * tanHalfFov);
        m(1,1) = 1.0 / tanHalfFov;
        m(2,2) = - (far + near) / (far - near);
        m(2,3) = - (2.0 * far * near) / (far - near);
        m(3,2) = -1.0;
        m(3,3) = 0.0;

        return m;
    }

    Matrix4 lookAt(const Vector3& eye, const Vector3& center, const Vector3& up)
    {
        const Vector3 f = Vector::normalize(center - eye);
        const Vector3 s = Vector::normalize(f.cross(up));
        const Vector3 u = s.cross(f);

        Matrix4 m;

        m(0,0) =  s.at(0);
        m(0,1) =  s.at(1);
        m(0,2) =  s.at(2);

        m(1,0) =  u.at(0);
        m(1,1) =  u.at(1);
        m(1,2) =  u.at(2);

        m(2,0) = -f.at(0);
        m(2,1) = -f.at(1);
        m(2,2) = -f.at(2);

        m(0,3) = -s.dot(eye);
        m(1,3) = -u.dot(eye);
        m(2,3) =  f.dot(eye);

        return m;
    }
}