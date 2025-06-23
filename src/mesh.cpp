#include "mesh.h"


#define _USE_MATH_DEFINES
#include <cmath>

#include <iostream>

namespace jade {
    void add_malloc(void*, bool);
}

jade::Mesh::Mesh() : vao(0), vbo(0), ibo(0), indexed(false), index_ct(0)  {}

jade::Mesh::Mesh(GLfloat* vertices, GLsizei vertices_size, MeshFormat fmt) : ibo(0), indexed(false) {

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);

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

jade::Mesh::Mesh(GLfloat* vertices, GLsizei vertices_size, GLuint* indices, GLsizei indices_size, MeshFormat fmt) : indexed(true) {
    index_ct = indices_size / sizeof(unsigned int);

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glGenBuffers(1, &ibo);

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

void jade::Mesh::draw() {
    glBindVertexArray(vao);
    if (indexed) glDrawElements(GL_TRIANGLES, index_ct, GL_UNSIGNED_INT, nullptr);
    else glDrawArrays(GL_TRIANGLES, 0, index_ct);
}

jade::Mesh jade::Mesh::triangle(float l, bool t) {
    return triangle(l, sqrtf(l*l - l/2*l/2), t);
}

jade::Mesh jade::Mesh::triangle(float b, float h, bool t) {
    if (!t) {
        float* vertices = new float[6]{
            -b/2, -h/2,
             b/2, -h/2,
             0.0f, h/2
        };
        add_malloc(vertices, true);
        return Mesh(vertices, 6 * sizeof(float), MeshFormat::P);
    } else {
        float* vertices = new float[12]{
            -b/2, -h/2,     0.0f, 0.0f,
             b/2, -h/2,     1.0f, 0.0f,
             0.0f, h/2,     0.5f, 1.0f
        };
        add_malloc(vertices, true);
        return Mesh(vertices, 12 * sizeof(float), MeshFormat::PT);
    }
}

jade::Mesh jade::Mesh::square(float l, bool t) {
    return quad(l, l, t);
}

jade::Mesh jade::Mesh::quad(float w, float h, bool t) {
    if (!t) {
        float* vertices = new float[12]{
            -w/2,  h/2,
            -w/2, -h/2,
             w/2, -h/2,
             w/2, -h/2,
             w/2,  h/2,
            -w/2,  h/2
        };
        add_malloc(vertices, true);
        return Mesh(vertices, 12 * sizeof(float), MeshFormat::P);
    } else {
        float* vertices = new float[24]{
            -w/2,  h/2,     0.0f, 1.0f,
            -w/2, -h/2,     0.0f, 0.0f,
             w/2, -h/2,     1.0f, 0.0f,
             w/2, -h/2,     1.0f, 0.0f,
             w/2,  h/2,     1.0f, 1.0f,
            -w/2,  h/2,     0.0f, 1.0f
        };
        add_malloc(vertices, true);
        return Mesh(vertices, 24 * sizeof(float), MeshFormat::PT);
    }
}

jade::Mesh jade::Mesh::circle(float r, int n, bool t) {
    if (!t) {
        float* vertices = new float[n * 2 + 2];
        vertices[0] = vertices[1] = 0.0f;
        for (int i = 2; i < n * 2 + 2; i += 2) {
            float a = 2 * M_PI / n * (i - 2) / 2;
            vertices[i + 0] = r * cosf(a);
            vertices[i + 1] = r * sinf(a);
        }
        unsigned int* indices = new unsigned int[n * 3];
        for (int i = 0, j = 1; i < n * 3; i += 3, j++) {
            indices[i + 0] = j;
            indices[i + 1] = j < n ? j + 1 : 1;
            indices[i + 2] = 0;
        }
        add_malloc(vertices, true);
        add_malloc(indices, true);
        return Mesh(vertices, (n * 2 + 2) * sizeof(float), indices, n * 3 * sizeof(unsigned int), MeshFormat::P);
    } else {
        float* vertices = new float[n * 4 + 4];
        vertices[0] = vertices[1] = 0.0f;
        vertices[2] = vertices[3] = 0.5f;
        for (int i = 4; i < n * 4 + 4; i += 4) {
            float a = 2 * M_PI / n * (i - 4) / 4;
            vertices[i + 0] = r * cosf(a);
            vertices[i + 1] = r * sinf(a);
            vertices[i + 2] = vertices[i + 0] / 2.0f + 0.5f;
            vertices[i + 3] = vertices[i + 1] / 2.0f + 0.5f;
        }
        unsigned int* indices = new unsigned int[n * 3];
        for (int i = 0; i < n; i++) {
            indices[i + 0] = i;
            indices[i + 1] = i < n - 1 ? i + 1 : 0;
            indices[i + 2] = 0;
        }
        add_malloc(vertices, true);
        add_malloc(indices, true);
        return Mesh(vertices, (n * 4 + 4) * sizeof(float), indices, n * 3 * sizeof(unsigned int), MeshFormat::PT);
    }
}
