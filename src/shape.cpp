#include <jade/shape.h>
#include <jade/internal.h>

namespace jade::hidden {
    void assert_initialized(const std::string&);
} using jade::hidden::assert_initialized;

using jade::core::Color, jade::core::Origin;
using jade::backend::Mesh;
using jade::internal::context;

namespace jade::draw {

    Shape::Shape() : color(Color::black()) {}

    Shape::Shape(const Mesh& m, float w, float h, const Color& col) {
        assert_initialized("jade::draw::Shape::Shape()");
        
        init_width = w;
        init_height = h;
        mesh = m;
        color = col;
    }

    void Shape::draw() const {
        context.shape_shader.use();
        context.shape_shader.set_mat4("u_model", model);
        context.shape_shader.set_color("u_col", color);
        mesh.draw();
    }

    float Shape::get_width() const {
        return init_width * get_scale_x();
    }

    float Shape::get_height() const {
        return init_height * get_scale_y();
    }

    const Color& Shape::get_color() const {
        return color;
    }

    void Shape::scale_to_width(float w, bool maintain_aspect) {
        float aspect = get_width() / get_height();
        set_scale_x(w / init_width);
        if (maintain_aspect) set_scale_y(get_scale_x() / aspect);
    }

    void Shape::scale_to_height(float h, bool maintain_aspect) {
        float aspect = get_width() / get_height();
        set_scale_y(h / init_height);
        if (maintain_aspect) set_scale_x(get_scale_y() * aspect);
    }

    void Shape::set_color(const Color& color) {
        this->color = color;
    }

    Shape Shape::triangle(float s) { return Shape::triangle(s, Color::white(), Origin::Center); }
    Shape Shape::triangle(float s, const core::Color& color) { return Shape::triangle(s, color, Origin::Center); }
    Shape Shape::triangle(float s, core::Origin origin) { return Shape::triangle(s, Color::white(), origin); }
    Shape Shape::triangle(float b, float h) { return Shape::triangle(b, h, Color::white(), Origin::Center); }
    Shape Shape::triangle(float b, float h, const core::Color& color) { return Shape::triangle(b, h, color, Origin::Center); }
    Shape Shape::triangle(float b, float h, core::Origin origin) { return Shape::triangle(b, h, Color::white(), origin); }
    Shape Shape::square(float s) { return Shape::square(s, Color::white(), Origin::Center); }
    Shape Shape::square(float s, const core::Color& color) { return Shape::square(s, color, Origin::Center); }
    Shape Shape::square(float s, core::Origin origin) { return Shape::square(s, Color::white(), origin); }
    Shape Shape::rect(float w, float h) { return Shape::rect(w, h, Color::white(), Origin::Center); }
    Shape Shape::rect(float w, float h, const core::Color& color) { return Shape::rect(w, h, color, Origin::Center); }
    Shape Shape::rect(float w, float h, core::Origin origin) { return Shape::rect(w, h, Color::white(), origin); }
    Shape Shape::circle(float r, int n) { return Shape::circle(r, n, Color::white(), Origin::Center); }
    Shape Shape::circle(float r, int n, const core::Color& color) { return Shape::circle(r, n, color, Origin::Center); }
    Shape Shape::circle(float r, int n, core::Origin origin) { return Shape::circle(r, n, Color::white(), origin); }

    Shape Shape::triangle(float s, const Color& col, Origin og) {
        float h = glm::sqrt(s*s - s/2*s/2);
        return Shape(Mesh::triangle(s, false, xoff(s, og), yoff(h, og)), s, h, col);
    }

    Shape Shape::triangle(float b, float h, const Color& col, Origin og) {
        return Shape(Mesh::triangle(b, h, false, xoff(b, og), yoff(h, og)), b, h, col);
    }

    Shape Shape::square(float s, const Color& col, Origin og) {
        return Shape(Mesh::square(s, false, xoff(s, og), yoff(s, og)), s, s, col);
    }

    Shape Shape::rect(float w, float h, const Color& col, Origin og) {
        return Shape(Mesh::quad(w, h, false, xoff(w, og), yoff(h, og)), w, h, col);
    }

    Shape Shape::circle(float r, int n, const Color& col, Origin og) {
        return Shape(Mesh::circle(r, n, false, xoff(2*r, og), yoff(2*r, og)), 2*r, 2*r, col);
    }

    float Shape::xoff(float w, core::Origin origin) {
        if (origin == Origin::BottomLeft || origin == Origin::Left || origin == Origin::TopLeft)
            return w / 2.0f;
        else if (origin == Origin::BottomRight || origin == Origin::Right || origin == Origin::TopRight)
            return -w / 2.0f;
        else return 0.0f;
    }

    float Shape::yoff(float h, core::Origin origin) {
        if (origin == Origin::BottomLeft || origin == Origin::Bottom || origin == Origin::BottomRight)
            return h / 2.0f;
        else if (origin == Origin::TopLeft || origin == Origin::Top || origin == Origin::TopRight)
            return -h / 2.0f;
        else return 0.0f;
    }
}
