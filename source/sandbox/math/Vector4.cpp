#include <sandbox/math/Vector4.hpp>
#include <cstring>
#include <cassert>

namespace sb
{
    Vector4::Vector4()
    {
        _data = new real[4];
        _size = 4;
        
        _data[0] = static_cast<real>(0.);
        _data[1] = static_cast<real>(0.);
        _data[2] = static_cast<real>(0.);
        _data[3] = static_cast<real>(0.);
    }

    Vector4::Vector4(const std::vector<real>& v)
    {
        assert(v.size() == 4);

        _data = new real[4];
        _size = 4;

        _data[0] = v[0];
        _data[1] = v[1];
        _data[2] = v[2];
        _data[3] = v[3];
    }

    Vector4::Vector4(const std::initializer_list<real>& list)
    {
        assert(list.size() == 4);

        _data = new real[4];
        _size = 4;

        memcpy(_data, list.begin(), _size * sizeof(real));
    }

    Vector4::Vector4(const Vector& v)
    {
        assert(v.size() == 4);

        _data = new real[4];
        _size = 4;

        _data[0] = v.at(0);
        _data[1] = v.at(1);
        _data[2] = v.at(2);
        _data[3] = v.at(3);
    }

    Vector4::Vector4(const Vector4& v)
    {
        _data = new real[4];
        _size = 4;

        _data[0] = v._data[0];
        _data[1] = v._data[1];
        _data[2] = v._data[2];
        _data[3] = v._data[3];
    }

    Vector4::~Vector4()
    {
        if (_data != nullptr)
        {
            delete _data;
            _data = nullptr;
        }

        _size = 0;
    }
}