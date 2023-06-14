/** @file VAO.hpp
 *  @brief Vertex Array Object which stores vertex/normal/color values and texture coords.
 * 
 *  @author Marco Carletti
*/
#pragma once

#include <sandbox/math/Vector.hpp>

namespace sb
{
    class VAO
    {
    public:

        /*!
            @brief Constructor.

            Model data to be rendered.
            Vertices are (at least) the position coordinates in 3D (x, y, z).
            Each vertex could have also: normal 3D vector (nx, ny, nz), color 3D vector (r, g, b)
            and texture 2D coords (u, v).
            Additional per-vertex information must be added in a specific order, that is
            "position > normal > color > texture": if color is needed, also normal must be included.
            According to the per-vertex data, stride must be set as needed.

            Example:
            - position-only: per_vertex_data = {x, y, z}, stride = 3
            - position-normal: per_vertex_data = {x, y, z, nx, ny, nz}, stride = 6
            - position-normal-color: per_vertex_data = {x, y, z, nx, ny, nz, r, g, b}, stride = 9
            - position-normal-color-texture: per_vertex_data = {x, y, z, nx, ny, nz, r, g, b, u, v}, stride = 11

            @param vertices Per-vertex data in the format {position [normal [color [texture]]]}.
            @param indices If set, enables EBO (Elements Buffer Object). When vertices is really big, EBO reduces memory usage but it is slightly slower.
            @param stride Number of per-vertex data. Eg. position-only: stride = 3, position-normal: stride = 6, position-normal-color: stride = 9, position-normal-color-texture: stride = 11.
        */
        VAO(const std::vector<real>& vertices, const std::vector<uint>& indices = {}, uint stride = 3);

        //! Destructor.
        ~VAO();

        //! Draw call which binds the VAO object to the GPU.
        void draw() const;

    private:

        //! Binding index of the vertex array object.
        uint _vao{0};

        //! Binding index of the vertex buffer object.
        uint _vbo{0};

        //! Binding index of the elements buffer object.
        uint _ebo{0};

        //! Number of object vertices.
        uint _num_vertices{0};

        //! Number of faces.
        uint _num_elements{0};
    };
}
