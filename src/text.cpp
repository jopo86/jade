#include <jade/text.h>
#include <jade/internal.h>

namespace jade::hidden {
    void assert_initialized(const std::string&);
} using jade::hidden::assert_initialized;

using jade::core::Color, jade::core::Origin;
using jade::internal::context;
using jade::backend::Font, jade::backend::Glyph;

namespace jade::draw {

    std::unordered_map<std::pair<std::string, int>, Font, Text::FontKeyHash> Text::loaded_fonts;

    Text::Text() : p_font(nullptr) {}

    Text::Text(const std::string& text, const std::string& font_path, int font_size) 
        : Text(text, font_path, font_size, Color::white(), Origin::Center) {}

    Text::Text(const std::string& text, const std::string& font_path, int font_size, const core::Color& color) 
        : Text(text, font_path, font_size, color, Origin::Center) {}

    Text::Text(const std::string& text, const std::string& font_path, int font_size, core::Origin origin) 
        : Text(text, font_path, font_size, Color::white(), origin) {}

    Text::Text(const std::string& text, const std::string& font_path, int font_size, const Color& color, Origin origin) : vao(0), vbo(0) {
        assert_initialized("jade::draw::Text::Text()");

        this->text = text;
        this->color = color;
        this->origin = origin;

        if (loaded_fonts.find({ font_path, font_size }) == loaded_fonts.end()) {
            loaded_fonts.insert({ { font_path, font_size }, Font(font_path, font_size) });
        }
        p_font = &loaded_fonts[{ font_path, font_size }];

        init_width = (float)get_width();
        init_height = (float)get_height();

        glGenVertexArrays(1, &vao);
        glGenBuffers(1, &vbo);

        glBindVertexArray(vao);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);

        glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, nullptr, GL_DYNAMIC_DRAW);

        glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }

    void Text::draw() const {
        context.text_shader.use();
        context.text_shader.set_mat4("u_model", model);
        context.text_shader.set_color("u_col", color);
        
        glBindVertexArray(vao);

        int width = get_width(), height = get_height();

        float advance = 0.0f;
        for (char c : text) {
            Glyph g = p_font->glyphs[c];

            float x = g.bearing_x + advance;
            float y = (float)(g.bearing_y - g.height);
            float w = (float)g.width;
            float h = (float)g.height;

            if (origin == Origin::Bottom || origin == Origin::Center || origin == Origin::Top)
                x -= width / 2;
            else if (origin == Origin::BottomRight || origin == Origin::Right || origin == Origin::TopRight)
                x -= width;
            
            if (origin == Origin::Left || origin == Origin::Center || origin == Origin::Right)
                y -= height / 2;
            else if (origin == Origin::TopLeft || origin == Origin::Top || origin == Origin::TopRight)
                y -= height;

            float vertices[6][4] = {
                { x,     y + h,       0.0f, 0.0f },
                { x,     y,           0.0f, 1.0f },
                { x + w, y,           1.0f, 1.0f },

                { x,     y + h,       0.0f, 0.0f },
                { x + w, y,           1.0f, 1.0f },
                { x + w, y + h,       1.0f, 0.0f }
            };

            glBindTexture(GL_TEXTURE_2D, g.tex);
            glActiveTexture(GL_TEXTURE0);

            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);

            glDrawArrays(GL_TRIANGLES, 0, 6);

            advance += g.advance;
        }

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);
    }

    void Text::set_text(const std::string& text) {
        this->text = text;
    }

    void Text::set_color(const core::Color& color) {
        this->color = color;
    }

    int Text::get_width() const {
        return p_font->get_str_size(text).x;
    }

    int Text::get_height() const {
        return p_font->get_str_size(text).y;
    }

    const std::string& Text::get_text() const {
        return text;
    }

    const core::Color& Text::get_color() const {
        return color;
    }

    void Text::scale_to_width(float w, bool maintain_aspect) {
        float aspect = get_width() / get_height();
        set_scale_x(w / init_width);
        if (maintain_aspect) set_scale_y(get_scale_x() / aspect);
    }

    void Text::scale_to_height(float h, bool maintain_aspect) {
        float aspect = get_width() / get_height();
        set_scale_y(h / init_height);
        if (maintain_aspect) set_scale_x(get_scale_y() * aspect);
    }
}
