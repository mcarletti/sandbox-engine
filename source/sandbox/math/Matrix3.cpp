#include <sandbox/math/Matrix3.hpp>
#include <cstring>
#include <cassert>

namespace sb
{
    Matrix3::Matrix3()
    {
        _size = 9;
        _rows = 3;
        _cols = 3;

        _data = new real[_size];

        memset(_data, 0, _size * sizeof(real));
        _data[0] = (real)1.0;
        _data[4] = (real)1.0;
        _data[8] = (real)1.0;
    }

    Matrix3::Matrix3(const std::vector<real>& v)
    {
        assert (v.size() == 9);

        _size = 9;
        _rows = 3;
        _cols = 3;

        _data = new real[_size];

        memcpy(_data, v.data(), _size * sizeof(real));
    }

    Matrix3::Matrix3(const Matrix& m)
    {
        assert (m.size() == 9);

        _size = 9;
        _rows = 3;
        _cols = 3;

        _data = new real[_size];

        memcpy(_data, m.data(), _size * sizeof(real));
    }

    Matrix3::Matrix3(const Matrix3& m)
    {
        _size = 9;
        _rows = 3;
        _cols = 3;

        _data = new real[_size];

        memcpy(_data, m._data, _size * sizeof(real));
    }

    Matrix3::~Matrix3()
    {
        if (_data != nullptr)
        {
            delete _data;
            _data = nullptr;
        }

        _size = 0;
        _rows = 0;
        _cols = 0;
    }
}