#include <sandbox/graphics/Shader.hpp>
#include <sandbox/core/opengl.hpp>
#include <sandbox/utils/Logger.hpp>
#include <sandbox/utils/Loader.hpp>
#include <sstream>
#include <cassert>

namespace sb
{
    Shader* Shader::create(const std::string& vertex_shader_filename, const std::string& fragment_shader_filename)
    {
        std::string vertex_shader_text = utils::Loader::readFileTXT(vertex_shader_filename);
        std::string fragment_shader_text = utils::Loader::readFileTXT(fragment_shader_filename);

        const char* vertex_shader_source = vertex_shader_text.c_str();
        const char* fragment_shader_source = fragment_shader_text.c_str();

        int success;
        char message[512];
        std::stringstream ss;

        uint vertex_shader;
        vertex_shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertex_shader, 1, &vertex_shader_source, NULL);
        glCompileShader(vertex_shader);
        glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex_shader, 512, NULL, message);
            ss << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << message;
            utils::Logger::write(ss.str());
            return nullptr;
        }

        uint fragment_shader;
        fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(fragment_shader, 1, &fragment_shader_source, NULL);
        glCompileShader(fragment_shader);
        glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(vertex_shader, 512, NULL, message);
            ss << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << message;
            utils::Logger::write(ss.str());
            return nullptr;
        }

        uint shader_program;
        shader_program = glCreateProgram();

        glAttachShader(shader_program, vertex_shader);
        glAttachShader(shader_program, fragment_shader);
        glLinkProgram(shader_program);

        glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader_program, 512, NULL, message);
            ss << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << message;
            utils::Logger::write(ss.str());
            return nullptr;
        }

        glDeleteShader(vertex_shader);
        glDeleteShader(fragment_shader);

        Shader* shader = new Shader();
        shader->_shader_program = shader_program;

        return shader;
    }

    Shader::~Shader()
    {
        glDeleteShader(_shader_program);
    }

    uint Shader::id() const
    {
        return _shader_program;
    }

    void Shader::use() const
    {
        glUseProgram(_shader_program);
    }

    void Shader::setBool(const std::string& name, const bool& value) const
    {
        int loc = glGetUniformLocation(_shader_program, name.c_str());
        glUniform1i(loc, value);
    }

    void Shader::setInt(const std::string& name, const int& value) const
    {
        int loc = glGetUniformLocation(_shader_program, name.c_str());
        glUniform1i(loc, value);
    }

    void Shader::setReal(const std::string& name, const real& value) const
    {
        int loc = glGetUniformLocation(_shader_program, name.c_str());
#ifdef __DOUBLE_PRECISION
        glUniform1d(loc, value);
#else
        glUniform1f(loc, value);
#endif
    }

    void Shader::setVector(const std::string& name, const Vector& value) const
    {
        assert(!name.empty());
        assert(value.size() >= 2 && value.size() <= 4);

        int loc = glGetUniformLocation(_shader_program, name.c_str());

        switch (value.size())
        {
#ifdef __DOUBLE_PRECISION
            case 2: glUniform2dv(loc, 1, value.data()); break;
            case 3: glUniform3dv(loc, 1, value.data()); break;
            case 4: glUniform4dv(loc, 1, value.data()); break;
#else
            case 2: glUniform2fv(loc, 1, value.data()); break;
            case 3: glUniform3fv(loc, 1, value.data()); break;
            case 4: glUniform4fv(loc, 1, value.data()); break;
#endif
            default: break;
        }
    }

    void Shader::setMatrix(const std::string& name, const Matrix& value) const
    {
        assert(!name.empty());
        assert(value.rows() >= 2 && value.rows() <= 4);
        assert(value.cols() >= 2 && value.cols() <= 4);
        assert(value.rows() == value.cols());

        int loc = glGetUniformLocation(_shader_program, name.c_str());

        switch (value.size())
        {
#ifdef __DOUBLE_PRECISION
            case 2: glUniformMatrix2dv(loc, 1, GL_FALSE, value.data()); break;
            case 3: glUniformMatrix3dv(loc, 1, GL_FALSE, value.data()); break;
            case 4: glUniformMatrix4dv(loc, 1, GL_FALSE, value.data()); break;
#else
            case 2: glUniformMatrix2fv(loc, 1, GL_FALSE, value.data()); break;
            case 3: glUniformMatrix3fv(loc, 1, GL_FALSE, value.data()); break;
            case 4: glUniformMatrix4fv(loc, 1, GL_FALSE, value.data()); break;
#endif
            default: break;
        }
    }
}