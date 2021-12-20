/** @file Texture.hpp
 *  @brief Load image files and create GL texture objects.
 * 
 *  @author Marco Carletti
*/
#pragma once

#include <string>
#include <sandbox/core/opengl.hpp>

namespace sb
{
    class Texture
    {
    public:

        /*!
            @brief Constructor.

            Create an OpenGL texture object from an image file.

            @param filename Path to the image file to load.
            @param format Pixel format (eg. GL_RGB, GL_RGBA).
        */
        Texture(const std::string& filename, int format = GL_RGB, bool flip = false, int wrap_s_mode = GL_REPEAT, int wrap_t_mode = GL_REPEAT, int min_filter_mode = GL_LINEAR_MIPMAP_LINEAR, int max_filter_mode = GL_LINEAR);

        //! Destructor. Unbind current image and delete this texture object.
        ~Texture();

        //! Return the width of the texture in pixels.
        uint width() const;

        //! Return the height of the texture in pixels.
        uint height() const;

        //! Return the number of channels of the texture.
        uint channels() const;

        //! Activate and bind this texture object to texture target location.
        void bind(uint loc = 0) const;

    private:

        //! Unique index of the texture object.
        uint _texture_id{0};

        //! Width of the texture in pixels.
        uint _width{0};

        //! Height of the texture in pixels.
        uint _height{0};

        //! Number of channels of the texture (1 = GRAYSCALE, 3 = RGB, 4 = RGBA).
        uint _num_channels{0};
    };
}