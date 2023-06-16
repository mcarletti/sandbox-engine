#include <sandbox/math/Matrix4.hpp>
#include <cstring>
#include <cassert>

namespace sb
{
    Matrix4::Matrix4()
    {
        _size = 16;
        _rows = 4;
        _cols = 4;

        _data = new real[_size];

        memset(_data, 0, _size * sizeof(real));
        _data[0] = (real)1.0;
        _data[5] = (real)1.0;
        _data[10] = (real)1.0;
        _data[15] = (real)1.0;
    }

    Matrix4::Matrix4(const std::vector<real>& v)
    {
        assert (v.size() == 4);

        _size = 16;
        _rows = 4;
        _cols = 4;

        _data = new real[_size];

        memcpy(_data, v.data(), _size * sizeof(real));
    }

    Matrix4::Matrix4(const Matrix& m)
    {
        assert (m.size() == 16);

        _size = 16;
        _rows = 4;
        _cols = 4;

        _data = new real[_size];

        memcpy(_data, m.data(), _size * sizeof(real));
    }

    Matrix4::Matrix4(const Matrix4& m)
    {
        _size = 16;
        _rows = 4;
        _cols = 4;

        _data = new real[_size];

        memcpy(_data, m._data, _size * sizeof(real));
    }

    Matrix4::~Matrix4()
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