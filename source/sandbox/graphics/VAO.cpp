#include <sandbox/graphics/VAO.hpp>
#include <sandbox/core/opengl.hpp>
#include <cassert>

namespace sb
{
    VAO::VAO(const std::vector<real>& vertices, const std::vector<uint>& indices, uint stride)
    {
        assert(vertices.size() > 0);
        assert(stride > 0);

#ifdef __DOUBLE_PRECISION
        GLenum dtype = GL_DOUBLE;
#else
        GLenum dtype = GL_FLOAT;
#endif

        glGenVertexArrays(1, &_vao);
        glBindVertexArray(_vao);

        glGenBuffers(1, &_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, _vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(real) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

        if (!indices.empty())
        {
            glGenBuffers(1, &_ebo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);
        }

        uint loc_vertex_position = 0;
        glVertexAttribPointer(loc_vertex_position, 3, dtype, GL_FALSE, stride * sizeof(real), (void*)0);
        glEnableVertexAttribArray(loc_vertex_position);

        uint loc_vertex_normal = 1;
        glVertexAttribPointer(loc_vertex_normal, 3, dtype, GL_FALSE, stride * sizeof(real), (void*)(3 * sizeof(real)));
        glEnableVertexAttribArray(loc_vertex_normal);

        uint loc_vertex_color = 2;
        glVertexAttribPointer(loc_vertex_color, 3, dtype, GL_FALSE, stride * sizeof(real), (void*)(6 * sizeof(real)));
        glEnableVertexAttribArray(loc_vertex_color);

        uint loc_texcoords = 3;
        glVertexAttribPointer(loc_texcoords, 2, dtype, GL_FALSE, stride * sizeof(real), (void*)(9 * sizeof(real)));
        glEnableVertexAttribArray(loc_texcoords);

        _num_vertices = vertices.size() / stride;
        _num_elements = indices.size();
    }

    VAO::~VAO()
    {
        glBindVertexArray(0);
        glDeleteVertexArrays(1, &_vao);
        glDeleteBuffers(1, &_vbo);
        glDeleteBuffers(1, &_ebo);
    }

    void VAO::draw() const
    {
        glBindVertexArray(_vao);

        if (_ebo == 0)
            glDrawArrays(GL_TRIANGLES, 0, _num_vertices);
        else
            glDrawElements(GL_TRIANGLES, _num_elements, GL_UNSIGNED_INT, 0);
        
        glBindVertexArray(0);
    }
}