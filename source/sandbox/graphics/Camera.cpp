#include <sandbox/graphics/Camera.hpp>
#include <sandbox/math/projection.hpp>
#include <sandbox/core/constants.hpp>
#include <sandbox/math/transform.hpp>
#include <sandbox/math/Vector2.hpp>
#include <sandbox/math/Vector3.hpp>

namespace sb
{
    Camera::Camera(Window* win, real fovy, real near, real far) :
        _window(win),  
        _fovy(fovy),
        _near(near),
        _far(far)
    {
        assert(_window != nullptr);
        assert(_fovy > 0 && _fovy < 360);
        assert(_near >= 0);
        assert(_far > _near);
    }

    Camera::~Camera()
    {
        _window = nullptr;
    }

    void Camera::update()
    {
        real aspect_ratio = 0;

        if (_viewport[3] > 0)
        {
            aspect_ratio = (real)_viewport[2] / _viewport[3];
        }
        else
        {
            real W = (real)_window->width();
            real H = (real)_window->height();
            aspect_ratio = W / H;
        }

        _projection = perspective(_fovy * DEG2RAD, aspect_ratio, _near, _far);
        _view = lookAt(_position, _position + _front, _up);
    }

    const Vector3& Camera::position() const
    {
        return _position;
    }

    const Vector3& Camera::front() const
    {
        return _front;
    }

    const Vector3& Camera::up() const
    {
        return _up;
    }

    const Matrix4& Camera::projection() const
    {
        return _projection;
    }

    const Matrix4& Camera::view() const
    {
        return _view;
    }

    real Camera::speed() const
    {
        return _speed;
    }

    real Camera::angularSpeed() const
    {
        return _angular_speed;
    }

    void Camera::setSpeed(real speed)
    {
        assert(speed >= 0);
        _speed = speed;
    }

    void Camera::setAngularSpeed(real speed)
    {
        assert(speed >= 0);
        _angular_speed = speed;
    }

    void Camera::setViewport(uint x, uint y, uint width, uint height)
    {
        assert(width > 0 && height > 0);

        _viewport[0] = x;
        _viewport[1] = y;
        _viewport[2] = width;
        _viewport[3] = height;

        glViewport(x, y, width, height);
        update();
    }

    void Camera::move(real dt, const Vector3& direction)
    {
        assert(direction.norm() > 0);
        _position += direction * _speed * dt;
    }

    void Camera::moveForward(real dt)
    {
        _position += _front * _speed * dt;
    }

    void Camera::moveBackward(real dt)
    {
        _position -= _front * _speed * dt;
    }

    void Camera::moveLeft(real dt)
    {
        _position -= _front.cross(_up) * _speed * dt;
    }

    void Camera::moveRight(real dt)
    {
        _position += _front.cross(_up) * _speed * dt;
    }

    void Camera::moveUp(real dt)
    {
        _position += _up * _speed * dt;
    }

    void Camera::moveDown(real dt)
    {
        _position -= _up * _speed * dt;
    }

    void Camera::rotateView(real dt, real dx, real dy)
    {
        assert(dx != 0 || dy != 0);
        
        Vector2 dir = Vector2::normalize({dx, dy});

        if (Vector3::normalize(_front).dot(_world_up) < (0.707))
            yaw(dir[0] * dt);
        pitch(dir[1] * dt);

        Vector3 right = Vector3::normalize(_front.cross(_world_up));
        _up = Vector3::normalize(right.cross(_front));
    }

    void Camera::roll(real dt)
    {
        _up = rotate(_up, _angular_speed * dt, _front);
    }

    void Camera::pitch(real dt)
    {
        Vector3 right = _front.cross(_up);
        _up = rotate(_up, _angular_speed * dt, right);
        _front = rotate(_front, _angular_speed * dt, right);
    }

    void Camera::yaw(real dt)
    {
        _front = rotate(_front, _angular_speed * dt, _up);
    }
}