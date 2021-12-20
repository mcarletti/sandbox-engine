#include <sandbox/graphics/Texture.hpp>
#include <sandbox/core/types.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include <externals/stb_image.h>

namespace sb
{
    Texture::Texture(const std::string& filename, int format, bool flip, int wrap_s_mode, int wrap_t_mode, int min_filter_mode, int max_filter_mode)
    {
        // FIXME: currently, our texture class supports only 3 and 4 channels images
        assert(format == GL_RGB || format == GL_RGBA);

        // like VAOs, texture objects must be generated
        // and "activated" through texture binding
        glGenTextures(1, &_texture_id);
        glBindTexture(GL_TEXTURE_2D, _texture_id);

        // set the texture wrapping/filtering options (on the currently bound texture object)
        // available options are: GL_REPEAT, GL_MIRRORED_REPEAT, GL_CLAMP_TO_EDGE, GL_CLAMP_TO_BORDER
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap_s_mode);	
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap_t_mode);

        // set interpolation mode when zoom in/out the image
        // available options are: GL_NEAREST, GL_LINEAR
        // if mipmaps are going to be generated: GL_LINEAR_MIPMAP_LINEAR, GL_LINEAR_MIPMAP_NEAREST, GL_NEAREST_MIPMAP_LINEAR, GL_NEAREST_MIPMAP_NEAREST
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, min_filter_mode);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, max_filter_mode);

        // load and generate the texture
        int x, y, comp;
        stbi_set_flip_vertically_on_load(flip);
        uchar *data = stbi_load(filename.c_str(), &x, &y, &comp, 0);
        assert (data != nullptr);

        _width = static_cast<uint>(x);
        _height = static_cast<uint>(y);
        _num_channels = static_cast<uint>(comp);

        // Pixel values are grouped into sets of one, two, three, or four values, depending on format, to form elements.
        // FIXME: currently, internal_format and format are set to be the same.
        int internal_format = format;
        glTexImage2D(GL_TEXTURE_2D, 0, internal_format, _width, _height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glBindTexture(GL_TEXTURE_2D, 0);
        stbi_image_free(data);
    }

    Texture::~Texture()
    {
        glBindTexture(GL_TEXTURE_2D, 0);
        glDeleteTextures(1, &_texture_id);
        _texture_id = 0;
        _width = 0;
        _height = 0;
        _num_channels = 0;
    }

    uint Texture::width() const
    {
        return _width;
    }

    uint Texture::height() const
    {
        return _height;
    }

    uint Texture::channels() const
    {
        return _num_channels;
    }

    void Texture::bind(uint loc) const
    {
        glActiveTexture(GL_TEXTURE0 + loc);
        glBindTexture(GL_TEXTURE_2D, _texture_id);
    }
}