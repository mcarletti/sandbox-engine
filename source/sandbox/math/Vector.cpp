#include <sandbox/math/Vector.hpp>
#include <cmath>
#include <cstring>
#include <cassert>

namespace sb
{
    Vector::Vector(const uint size)
    {
        assert(size > 0);

        _data = new real[size];
        _size = size;

        memset(_data, 0, _size * sizeof(real));
    }

    Vector::Vector(const std::vector<real>& v)
    {
        assert(v.size() > 0);

        _data = new real[v.size()];
        _size = v.size();

        memcpy(_data, v.data(), _size * sizeof(real));
    }

    Vector::Vector(const std::initializer_list<real>& list)
    {
        assert(list.size() > 0);

        _data = new real[list.size()];
        _size = list.size();

        memcpy(_data, list.begin(), _size * sizeof(real));
    }

    Vector::Vector(const Vector& v)
    {
        _data = new real[v._size];
        _size = v._size;

        memcpy(_data, v._data, _size * sizeof(real));
    }

    Vector::~Vector()
    {
        if (_data != nullptr)
        {
            delete _data;
            _data = nullptr;
        }

        _size = 0;
    }

    const real* Vector::data() const
    {
        return _data;
    }

    uint Vector::size() const
    {
        return _size;
    }

    real& Vector::operator[](uint i)
    {
        assert(i < _size);
        return _data[i];
    }

    real& Vector::operator()(const uint i)
    {
        assert(i < _size);
        return _data[i];
    }

    real Vector::at(const uint i) const
    {
        assert(i < _size);
        return _data[i];
    }

    real Vector::norm() const
    {
        assert(_size > 0);

        real sum_of_squares = 0;

        for (uint i = 0; i < _size; ++i)
            sum_of_squares += _data[i] * _data[i];

        return sqrt(sum_of_squares);
    }

    Vector Vector::normalize() const
    {
        assert(_size > 0);

        Vector res(*this);

        // get the min and max values of the array
        real min_value = SB_REAL_MAX;
        real max_value = SB_REAL_MIN;
        for (uint i = 0; i < _size; ++i)
        {
            if (_data[i] < min_value)
                min_value = _data[i];
            if (_data[i] > max_value)
                max_value = _data[i];
        }

        // shift the array by removing the minimum value
        // from each element so that the array starts from 0
        for (uint i = 0; i < _size; ++i)
            res._data[i] -= min_value;

        // update the max value and normalize the vector
        max_value -= min_value;
        if (max_value > 0)
            for (uint i = 0; i < _size; ++i)
                res._data[i] /= max_value;

        return res;
    }

    real Vector::dot(const Vector& v) const
    {
        assert(_size == v._size);

        real res = 0;
        for (uint i = 0; i < _size; ++i)
            res += _data[i] * v._data[i];
        return res;
    }

    real Vector::angle(const Vector& v) const
    {
        assert(_size == v._size);

        real l1 = norm();
        real l2 = v.norm();
        assert(l1 > 0 && l2 > 0);

        return acos(dot(v) / (l1 * l2));
    }

    Vector Vector::cross(const Vector& v) const
    {
        assert(_size == v._size);
        assert(_size == 3);

        Vector res(3);
        res[0] = _data[1] * v._data[2] - _data[2] * v._data[1];
        res[1] = _data[2] * v._data[0] - _data[0] * v._data[2];
        res[2] = _data[0] * v._data[1] - _data[1] * v._data[0];
        return res;
    }

    bool Vector::operator==(const Vector& v) const
    {
        assert(_size == v._size);

        bool res = true;

        for (uint i = 0; i < _size; ++i)
            res &= _data[i] == v._data[i];

        return res;
    }

    void Vector::operator=(const Vector& v)
    {
        assert(_size == v._size);
        memcpy(_data, v._data, _size * sizeof(real));
    }

    Vector Vector::operator+(const real& v) const
    {
        Vector res(_size);
        for (uint i = 0; i < _size; ++i)
            res._data[i] = _data[i] + v;
        return res;
    }

    void Vector::operator+=(const real& v)
    {
        for (uint i = 0; i < _size; ++i)
            _data[i] += v;
    }

    Vector Vector::operator-(const real& v) const
    {
        Vector res(_size);
        for (uint i = 0; i < _size; ++i)
            res._data[i] = _data[i] - v;
        return res;
    }

    void Vector::operator-=(const real& v)
    {
        for (uint i = 0; i < _size; ++i)
            _data[i] -= v;
    }

    Vector Vector::operator-() const
    {
        Vector res(_size);
        for (uint i = 0; i < _size; ++i)
            res._data[i] = -_data[i];
        return res;
    }

    Vector Vector::operator*(const real& v) const
    {
        Vector res(_size);
        for (uint i = 0; i < _size; ++i)
            res._data[i] = _data[i] * v;
        return res;
    }

    void Vector::operator*=(const real& v)
    {
        for (uint i = 0; i < _size; ++i)
            _data[i] *= v;
    }

    Vector Vector::operator/(const real& v) const
    {
        assert(v != 0);

        Vector res(_size);
        for (uint i = 0; i < _size; ++i)
            res._data[i] = _data[i] / v;
        return res;
    }

    void Vector::operator/=(const real& v)
    {
        assert(v != 0);

        for (uint i = 0; i < _size; ++i)
            _data[i] /= v;
    }

    Vector Vector::operator+(const Vector& v) const
    {
        assert(_size == v._size);

        Vector res(_size);
        for (uint i = 0; i < _size; ++i)
            res._data[i] = _data[i] + v._data[i];
        return res;
    }

    void Vector::operator+=(const Vector& v)
    {
        assert(_size == v._size);

        for (uint i = 0; i < _size; ++i)
            _data[i] += v._data[i];
    }

    Vector Vector::operator-(const Vector& v) const
    {
        assert(_size == v._size);

        Vector res(_size);
        for (uint i = 0; i < _size; ++i)
            res._data[i] = _data[i] - v._data[i];
        return res;
    }

    void Vector::operator-=(const Vector& v)
    {
        assert(_size == v._size);

        for (uint i = 0; i < _size; ++i)
            _data[i] -= v._data[i];
    }

    Vector Vector::operator*(const Vector& v) const
    {
        assert(_size == v._size);

        Vector res(_size);
        for (uint i = 0; i < _size; ++i)
            res._data[i] = _data[i] * v._data[i];
        return res;
    }

    void Vector::operator*=(const Vector& v)
    {
        assert(_size == v._size);

        for (uint i = 0; i < _size; ++i)
            _data[i] *= v._data[i];
    }

    Vector Vector::operator/(const Vector& v) const
    {
        assert(_size == v._size);

        Vector res(_size);
        for (uint i = 0; i < _size; ++i)
        {
            assert(v._data[i] != 0);
            res._data[i] = _data[i] / v._data[i];
        }
        return res;
    }

    void Vector::operator/=(const Vector& v)
    {
        assert(_size == v._size);

        for (uint i = 0; i < _size; ++i)
        {
            assert(v._data[i] != 0);
            _data[i] /= v._data[i];
        }
    }
}