#include <sandbox/math/Vector2.hpp>
#include <cassert>

namespace sb
{
    Vector2::Vector2()
    {
        _data = new real[2];
        _size = 2;
        
        _data[0] = static_cast<real>(0.);
        _data[1] = static_cast<real>(0.);
    }

    Vector2::Vector2(const std::vector<real>& v)
    {
        assert(v.size() == 2);

        _data = new real[2];
        _size = 2;

        _data[0] = v[0];
        _data[1] = v[1];
    }

    Vector2::Vector2(const Vector& v)
    {
        assert(v.size() == 2);

        _data = new real[2];
        _size = 2;

        _data[0] = v.at(0);
        _data[1] = v.at(1);
    }

    Vector2::Vector2(const Vector2& v)
    {
        _data = new real[2];
        _size = 2;

        _data[0] = v._data[0];
        _data[1] = v._data[1];
    }

    Vector2::~Vector2()
    {
        if (_data != nullptr)
        {
            delete _data;
            _data = nullptr;
        }

        _size = 0;
    }
}