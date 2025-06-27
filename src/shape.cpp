#include "shape.h"
#include "internal.h"

namespace jade::hidden {
    void assert_initialized(const std::string&);
} using jade::hidden::assert_initialized;

using jade::core::Color;
using jade::backend::Mesh;
using jade::internal::context;

namespace jade::draw {

    Shape::Shape() : color(Color::black()) {
        model = glm::mat4(1.0f);
    }

    Shape::Shape(const Mesh& mesh, const Color& color) {
        assert_initialized("jade::draw::Shape::Shape()");
        
        model = glm::mat4(1.0f);
        this->mesh = mesh;
        this->color = color;
    }

    void Shape::draw() {
        context.shape_shader.use();
        context.shape_shader.set_mat4("u_model", model);
        context.shape_shader.set_color("u_col", color);
        mesh.draw();
    }

    void Shape::set_color(const Color& color) {
        this->color = color;
    }

    const Color& Shape::get_color() {
        return color;
    }

    Shape Shape::triangle(float s, const Color& col) {
        return Shape(Mesh::triangle(s, false), col);
    }

    Shape Shape::triangle(float b, float h, const Color& col) {
        return Shape(Mesh::triangle(b, h, false), col);
    }

    Shape Shape::square(float s, const Color& col) {
        return Shape(Mesh::square(s, false), col);
    }

    Shape Shape::quad(float w, float h, const Color& col) {
        return Shape(Mesh::quad(w, h, false), col);
    }

    Shape Shape::circle(float r, int n, const Color& col) {
        return Shape(Mesh::circle(r, n, false), col);
    }
}
