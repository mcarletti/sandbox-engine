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

        m(0,0) =  s.x;
        m(1,0) =  s.y;
        m(2,0) =  s.z;

        m(0,1) =  u.x;
        m(1,1) =  u.y;
        m(2,1) =  u.z;

        m(0,2) = -f.x;
        m(1,2) = -f.y;
        m(2,2) = -f.z;

        m(3,0) = -s.dot(eye);
        m(3,1) = -u.dot(eye);
        m(3,2) =  f.dot(eye);

        return m;
    }
}