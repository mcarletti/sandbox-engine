/** @file Shader.hpp
 *  @brief Load, compile and use OpenGL/GLSL shader files.
 * 
 *  @author Marco Carletti
*/
#pragma once

#include <string>
#include <sandbox/math/Vector.hpp>
#include <sandbox/math/Matrix.hpp>

namespace sb
{
    class Shader
    {
    public:

        /*!
            @brief Static constructor-like function.

            Return a pointer to a shader program if vertex/fragment shaders compile.

            @param vertex_shader_filename Complete path to the vertex shader text file.
            @param fragment_shader_filename Complete path to the fragment shader text file.

            @return Pointer to a valid Shader object. Nullptr if not valid.
        */
        static Shader* create(const std::string& vertex_shader_filename, const std::string& fragment_shader_filename);
        ~Shader();

        //! Return shader unique id.
        uint id() const;

        //! Enable/activate this shader.
        void use() const;

        /*!
            @brief Set bool uniform value. If named uniform does not exist, do nothing.

            @param name Name of the uniform variable to be set.
            @param value New value of the named uniform.
        */
        void setBool(const std::string& name, const bool& value) const;

        /*!
            @brief Set integer uniform value. If named uniform does not exist, do nothing.

            @param name Name of the uniform variable to be set.
            @param value New value of the named uniform.
        */
        void setInt(const std::string& name, const int& value) const;

        /*!
            @brief Set float uniform value. If named uniform does not exist, do nothing.

            @param name Name of the uniform variable to be set.
            @param value New value of the named uniform.
        */
        void setReal(const std::string& name, const float& value) const;

        /*!
            @brief Set vector uniform value. If named uniform does not exist, do nothing.

            @param name Name of the uniform variable to be set.
            @param v New vector of the named uniform.
        */
        void setVector(const std::string& name, const Vector& v) const;

        /*!
            @brief Set matrix uniform value. If named uniform does not exist, do nothing.

            @param name Name of the uniform variable to be set.
            @param m New matrix value of the named uniform.
        */
        void setMatrix(const std::string& name, const Matrix& m) const;

    private:

        //! Default constructor.
        Shader() = default;

        //! Unique id of the shader program.
        uint _shader_program{0};
    };
}