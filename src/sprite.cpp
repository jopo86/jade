#include <jade/sprite.h>
#include <jade/internal.h>

namespace jade::hidden {
    void assert_initialized(const std::string&);
} using jade::hidden::assert_initialized;

using jade::core::Origin;
using jade::backend::Mesh, jade::backend::Texture;
using jade::internal::context;

namespace jade::draw {

    Sprite::Sprite() {}

    Sprite::Sprite(const std::string& path, Origin origin) {
        assert_initialized("jade::draw::Sprite::Sprite()");
        tex = Texture(path);
        init_width = (float)tex.width;
        init_height = (float)tex.height;

        float xoff = 0.0f, yoff = 0.0f;
        if (origin == Origin::BottomLeft || origin == Origin::Left || origin == Origin::TopLeft)
            xoff += init_width / 2.0f;
        else if (origin == Origin::BottomRight || origin == Origin::Right || origin == Origin::TopRight)
            xoff -= init_width / 2.0f;
        
        if (origin == Origin::BottomLeft || origin == Origin::Bottom || origin == Origin::BottomRight)
            yoff += init_height / 2.0f;
        else if (origin == Origin::TopLeft || origin == Origin::Top || origin == Origin::TopRight)
            yoff -= init_height / 2.0f;

        mesh = Mesh::quad(init_width, init_height, true, xoff, yoff);
    }

    void Sprite::draw() const {
        context.sprite_shader.use();
        context.sprite_shader.set_mat4("u_model", model);
        tex.bind();
        mesh.draw();
    }

    float Sprite::get_width() const {
        return init_width * get_scale_x();
    }

    float Sprite::get_height() const {
        return init_height * get_scale_y();
    }

    void Sprite::scale_to_width(float w, bool maintain_aspect) {
        float aspect = get_width() / get_height();
        set_scale_x(w / init_width);
        if (maintain_aspect) set_scale_y(get_scale_x() / aspect);
    }

    void Sprite::scale_to_height(float h, bool maintain_aspect) {
        float aspect = get_width() / get_height();
        set_scale_y(h / init_height);
        if (maintain_aspect) set_scale_x(get_scale_y() * aspect);
    }
}
