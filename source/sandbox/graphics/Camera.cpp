#include <sandbox/graphics/Camera.hpp>
#include <sandbox/math/projection.hpp>
#include <sandbox/core/constants.hpp>

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
        sb::real aspect_ratio = 0;

        if (_viewport[3] > 0)
        {
            aspect_ratio = (sb::real)_viewport[2] / _viewport[3];
        }
        else
        {
            sb::real W = (sb::real)_window->width();
            sb::real H = (sb::real)_window->height();
            aspect_ratio = W / H;
        }

        _projection = sb::perspective(_fovy * sb::DEG2RAD, aspect_ratio, _near, _far);
        _view = sb::lookAt(_position, _position + _front, _up);
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

    void Camera::setSpeed(real speed)
    {
        assert(speed >= 0);
        _speed = speed;
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
}