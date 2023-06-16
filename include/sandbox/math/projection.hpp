/** @file projection.hpp
 *  @brief Coordinate system utilities.
 * 
 *  @author Marco Carletti
*/
#pragma once

#include <sandbox/math/Vector3.hpp>
#include <sandbox/math/Matrix4.hpp>

namespace sb
{
    /*!
        @brief Create an orthographic projection matrix.

        @param left The left edge of the view frustum.
        @param right The right edge of the view frustum.
        @param bottom The bottom edge of the view frustum.
        @param top The top edge of the view frustum.
        @param near The near edge of the view frustum.
        @param far The far edge of the view frustum.
    */
    Matrix4 ortho(const real left, const real right, const real bottom, const real top, const real near, const real far);

    /*!
        @brief Create a perspective projection matrix.
        
        @param fov The field of view in radians.
        @param aspect The aspect ratio of the view frustum.
        @param near The near edge of the view frustum.
        @param far The far edge of the view frustum.
    */
    Matrix4 perspective(const real fov, const real aspect, const real near, const real far);

    /*!
        @brief Create a look at matrix.

        @param eye The position of the camera.
        @param center The position of the object to look at.
        @param up The up vector.
    */
    Matrix4 lookAt(const Vector3& eye, const Vector3& center, const Vector3& up);
}