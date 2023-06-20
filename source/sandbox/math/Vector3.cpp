#include <sandbox/math/Vector3.hpp>
#include <cstring>
#include <cassert>

namespace sb
{
    Vector3::Vector3()
    {
        _data = new real[3];
        _size = 3;
        
        _data[0] = static_cast<real>(0.);
        _data[1] = static_cast<real>(0.);
        _data[2] = static_cast<real>(0.);
    }

    Vector3::Vector3(const std::vector<real>& v)
    {
        assert(v.size() == 3);

        _data = new real[3];
        _size = 3;

        _data[0] = v[0];
        _data[1] = v[1];
        _data[2] = v[2];
    }

    Vector3::Vector3(const std::initializer_list<real>& list)
    {
        assert(list.size() == 3);

        _data = new real[3];
        _size = 3;

        memcpy(_data, list.begin(), _size * sizeof(real));
    }

    Vector3::Vector3(const Vector& v)
    {
        assert(v.size() == 3);

        _data = new real[3];
        _size = 3;

        _data[0] = v.at(0);
        _data[1] = v.at(1);
        _data[2] = v.at(2);
    }

    Vector3::Vector3(const Vector3& v)
    {
        _data = new real[3];
        _size = 3;

        _data[0] = v._data[0];
        _data[1] = v._data[1];
        _data[2] = v._data[2];
    }

    Vector3::~Vector3()
    {
        if (_data != nullptr)
        {
            delete _data;
            _data = nullptr;
        }

        _size = 0;
    }
}