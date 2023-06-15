#include <sandbox/math/Matrix2.hpp>
#include <cstring>
#include <cassert>

namespace sb
{
    Matrix2::Matrix2()
    {
        _size = 4;
        _rows = 2;
        _cols = 2;

        _data = new real[_size];

        memset(_data, 0, _size * sizeof(real));
        _data[0] = (real)1.0;
        _data[3] = (real)1.0;
    }

    Matrix2::Matrix2(const std::vector<real>& v)
    {
        assert (v.size() == 4);

        _size = 4;
        _rows = 2;
        _cols = 2;

        _data = new real[_size];

        memcpy(_data, v.data(), _size * sizeof(real));
    }

    Matrix2::Matrix2(const Matrix2& m)
    {
        _size = 4;
        _rows = 2;
        _cols = 2;

        _data = new real[_size];

        memcpy(_data, m._data, _size * sizeof(real));
    }

    Matrix2::~Matrix2()
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