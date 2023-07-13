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
            const Vector3& position() const;

            //! Return camera front vector.
            const Vector3& front() const;

            //! Return camera up vector.
            const Vector3& up() const;

            //! Return camera projection matrix.
            const Matrix4& projection() const;

            //! Return camera view matrix.
            const Matrix4& view() const;

            //! Return camera translation speed.
            real speed() const;

            //! Return camera rotation speed.
            real angularSpeed() const;

            //! Set camera translation speed.
            void setSpeed(real speed);

            //! Set camera rotation speed.
            void setAngularSpeed(real speed);

            //! Set viewport.
            void setViewport(uint x, uint y, uint width, uint height);

            //! Move along the given direction.
            void move(real dt, const Vector3& direction);

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

            //! Rotate camera view by an offset in the image plane.
            void rotateView(real dt, real dx, real dy);

            //! Rotate camera along the front vector.
            void roll(real dt);

            //! Rotate camera along the right vector.
            void pitch(real dt);

            //! Rotate camera along the up vector.
            void yaw(real dt);

        private:

            //! Pointer to a valid Window object.
            Window* _window{nullptr};

            //! Camera position.
            Vector3 _position{0., 0., 3.};

            //! Camera front vector.
            Vector3 _front{0., 0., -1.};

            //! Camera up vector.
            Vector3 _up{0., 1., 0.};

            //! World up vector.
            Vector3 _world_up{0., 1., 0.};

            //! Translation speed in units per second.
            real _speed{5.};

            //! Rotation speed in radians.
            real _angular_speed{3.};

            //! Projection matrix field of view.
            real _fovy{45.};

            //! Projection matrix near plane.
            real _near{0.1};

            //! Projection matrix far plane.
            real _far{100.};

            //! Projection matrix.
            Matrix4 _projection;

            //! View matrix.
            Matrix4 _view;

            //! Viewport (x, y, width, height).
            uint _viewport[4]{0, 0, 0, 0};
    };
}