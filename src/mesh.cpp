#include "mesh.h"
#include "internal.h"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

using jade::internal::allocs;

namespace jade::hidden {
    void assert_initialized(const std::string&);
} using jade::hidden::assert_initialized;

namespace jade::backend {
    
    Mesh::Mesh() : vao(0), vbo(0), ibo(0), indexed(false), index_ct(0)  {}

    Mesh::Mesh(GLfloat* vertices, GLsizei vertices_size, MeshFormat fmt) : ibo(0), indexed(false) {
        assert_initialized("jade::backend::Mesh::Mesh()");
        
        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        allocs.vaos.push_back(vao);
        allocs.bufs.push_back(vbo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        switch (fmt) {
            case MeshFormat::P:
                index_ct = vertices_size / sizeof(float) / 2;
                glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
                glEnableVertexAttribArray(0);
                break;
            case MeshFormat::PT:
                index_ct = vertices_size / sizeof(float) / 4;
                glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
                glEnableVertexAttribArray(0);
                glEnableVertexAttribArray(1);
                break;
        }

        glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    Mesh::Mesh(GLfloat* vertices, GLsizei vertices_size, GLuint* indices, GLsizei indices_size, MeshFormat fmt) : indexed(true) {
        assert_initialized("jade::backend::Mesh::Mesh()");
        
        index_ct = indices_size / sizeof(unsigned int);

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);
        glGenBuffers(1, &ibo);
        allocs.vaos.push_back(vao);
        allocs.bufs.push_back(vbo);
        allocs.bufs.push_back(ibo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);

        switch (fmt) {
            case MeshFormat::P:
                glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
                glEnableVertexAttribArray(0);
                break;
            case MeshFormat::PT:
                glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
                glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
                glEnableVertexAttribArray(0);
                glEnableVertexAttribArray(1);
                break;
        }

        glBufferData(GL_ARRAY_BUFFER, vertices_size, vertices, GL_STATIC_DRAW);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, indices, GL_STATIC_DRAW);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    void Mesh::draw() {
        glBindVertexArray(vao);
        if (indexed) glDrawElements(GL_TRIANGLES, index_ct, GL_UNSIGNED_INT, nullptr);
        else glDrawArrays(GL_TRIANGLES, 0, index_ct);
    }

    Mesh Mesh::triangle(float s, bool t, float xoff, float yoff) {
        return triangle(s, glm::sqrt(s*s - s/2*s/2), t, xoff, yoff);
    }

    Mesh Mesh::triangle(float b, float h, bool t, float xoff, float yoff) {
        if (!t) {
            float* vertices = new float[6]{
                -b/2 + xoff, -h/2 + yoff,
                b/2 + xoff, -h/2 + yoff,
                0.0f + xoff, h/2 + yoff
            };
            allocs.arrs.push_back(vertices);
            return Mesh(vertices, 6 * sizeof(float), MeshFormat::P);
        } else {
            float* vertices = new float[12]{
                -b/2 + xoff, -h/2 + yoff,     0.0f, 0.0f,
                b/2 + xoff, -h/2 + yoff,     1.0f, 0.0f,
                0.0f + xoff, h/2 + yoff,     0.5f, 1.0f
            };
            allocs.arrs.push_back(vertices);
            return Mesh(vertices, 12 * sizeof(float), MeshFormat::PT);
        }
    }

    Mesh Mesh::square(float l, bool t, float xoff, float yoff) {
        return quad(l, l, t, xoff, yoff);
    }

    Mesh Mesh::quad(float w, float h, bool t, float xoff, float yoff) {
        if (!t) {
            float* vertices = new float[12]{
                -w/2 + xoff,  h/2 + yoff,
                -w/2 + xoff, -h/2 + yoff,
                w/2 + xoff, -h/2 + yoff,
                w/2 + xoff, -h/2 + yoff,
                w/2 + xoff,  h/2 + yoff,
                -w/2 + xoff,  h/2 + yoff
            };
            allocs.arrs.push_back(vertices);
            return Mesh(vertices, 12 * sizeof(float), MeshFormat::P);
        } else {
            float* vertices = new float[24]{
                -w/2 + xoff,  h/2 + yoff,     0.0f, 1.0f,
                -w/2 + xoff, -h/2 + yoff,     0.0f, 0.0f,
                w/2 + xoff, -h/2 + yoff,     1.0f, 0.0f,
                w/2 + xoff, -h/2 + yoff,     1.0f, 0.0f,
                w/2 + xoff,  h/2 + yoff,     1.0f, 1.0f,
                -w/2 + xoff,  h/2 + yoff,     0.0f, 1.0f
            };
            allocs.arrs.push_back(vertices);
            return Mesh(vertices, 24 * sizeof(float), MeshFormat::PT);
        }
    }

    Mesh Mesh::circle(float r, int n, bool t, float xoff, float yoff) {
        if (!t) {
            float* vertices = new float[n * 2 + 2];
            vertices[0] = xoff;
            vertices[1] = yoff;
            for (int i = 2; i < n * 2 + 2; i += 2) {
                float a = glm::two_pi<float>() / n * (i - 2) / 2;
                vertices[i + 0] = r * glm::cos(a) + xoff;
                vertices[i + 1] = r * glm::sin(a) + yoff;
            }
            unsigned int* indices = new unsigned int[n * 3];
            for (int i = 0, j = 1; i < n * 3; i += 3, j++) {
                indices[i + 0] = j;
                indices[i + 1] = j < n ? j + 1 : 1;
                indices[i + 2] = 0;
            }
            allocs.arrs.push_back(vertices);
            allocs.arrs.push_back(indices);
            return Mesh(vertices, (n * 2 + 2) * sizeof(float), indices, n * 3 * sizeof(unsigned int), MeshFormat::P);
        } else {
            float* vertices = new float[n * 4 + 4];
            vertices[0] = xoff;
            vertices[1] = yoff;
            vertices[2] = vertices[3] = 0.5f;
            for (int i = 4; i < n * 4 + 4; i += 4) {
                float a = glm::two_pi<float>() / n * (i - 4) / 4;
                vertices[i + 0] = r * glm::cos(a) + xoff;
                vertices[i + 1] = r * glm::sin(a) + yoff;
                vertices[i + 2] = vertices[i + 0] / 2.0f + 0.5f;
                vertices[i + 3] = vertices[i + 1] / 2.0f + 0.5f;
            }
            unsigned int* indices = new unsigned int[n * 3];
            for (int i = 0; i < n; i++) {
                indices[i + 0] = i;
                indices[i + 1] = i < n - 1 ? i + 1 : 0;
                indices[i + 2] = 0;
            }
            allocs.arrs.push_back(vertices);
            allocs.arrs.push_back(indices);
            return Mesh(vertices, (n * 4 + 4) * sizeof(float), indices, n * 3 * sizeof(unsigned int), MeshFormat::PT);
        }
    }
}
