#pragma once

#include <glad/glad.h>

namespace jade {

    enum class MeshFormat {
        P,
        PT,
    };

    class Mesh {
    public:
        GLuint vao, vbo, ibo;
        bool indexed;
        GLsizei index_ct;

        Mesh();
        Mesh(GLfloat* vertices, GLsizei vertices_size, MeshFormat fmt);
        Mesh(GLfloat* vertices, GLsizei vertices_size, GLuint* indices, GLsizei indices_size, MeshFormat fmt);

        void draw();

        static Mesh triangle(float side_len, bool tex_coords);
        static Mesh triangle(float base, float height, bool tex_coords);
        static Mesh square(float side_len, bool tex_coords);
        static Mesh quad(float width, float height, bool tex_coords);
        static Mesh circle(float radius, int n_segments, bool tex_coords);
    };
};
