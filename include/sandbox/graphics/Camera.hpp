/** @file Camera.hpp
 *  @brief Class for camera.
 * 
 *  @author Marco Carletti
*/
#pragma once

#include <sandbox/core/Window.hpp>
#include <sandbox/math/Vector3.hpp>
#include <sandbox/math/Matrix4.hpp>

namespace sb
{
    class Camera
    {
        public:

            /*!
                @brief Constructor.

                @param win Pointer to a valid Window object.
                @param fovy Field of view in degrees.
                @param near Near plane.
                @param far Far plane.

                @return Pointer to a valid Camera object.
            */
            Camera(Window* win, real fovy = 45., real near = .1, real far = 100.);

            //! Destructor.
            ~Camera();

            //! Update camera.
            void update();

            //! Return camera position.
            const sb::Vector3& position() const;

            //! Return camera front vector.
            const sb::Vector3& front() const;

            //! Return camera up vector.
            const sb::Vector3& up() const;

            //! Return camera projection matrix.
            const sb::Matrix4& projection() const;

            //! Return camera view matrix.
            const sb::Matrix4& view() const;

            //! Return camera speed.
            real speed() const;

            //! Set camera speed.
            void setSpeed(real speed);

            //! Set viewport.
            void setViewport(uint x, uint y, uint width, uint height);

            //! Move along the front vector.
            void moveForward(real dt);

            //! Move along the back vector.
            void moveBackward(real dt);

            //! Move along the left vector.
            void moveLeft(real dt);

            //! Move along the right vector.
            void moveRight(real dt);

            //! Move along the up vector.
            void moveUp(real dt);

            //! Move along the down vector.
            void moveDown(real dt);

        private:

            //! Pointer to a valid Window object.
            sb::Window* _window{nullptr};

            //! Camera position.
            sb::Vector3 _position{0., 0., 3.};

            //! Camera front vector.
            sb::Vector3 _front{0., 0., -1.};

            //! Camera up vector.
            sb::Vector3 _up{0., 1., 0.};

            //! Camera world up vector.
            sb::real _speed{5.};

            //! Projection matrix field of view.
            sb::real _fovy{45.};

            //! Projection matrix near plane.
            sb::real _near{0.1};

            //! Projection matrix far plane.
            sb::real _far{100.};

            //! Projection matrix.
            sb::Matrix4 _projection;

            //! View matrix.
            sb::Matrix4 _view;

            //! Viewport (x, y, width, height).
            uint _viewport[4]{0, 0, 0, 0};
    };
}