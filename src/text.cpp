#include "text.h"
#include "internal.h"

namespace jade::hidden {
    void assert_initialized(const std::string&);
} using jade::hidden::assert_initialized;

using jade::core::Color, jade::core::Origin;
using jade::internal::context;
using jade::backend::Font, jade::backend::Glyph;

namespace jade::draw {

    Text::Text() : p_font(nullptr) {
        model = glm::mat4(1.0f);
    }

    Text::Text(const std::string& text, const std::string& font_path, const Color& color, Origin origin) {
        assert_initialized("jade::draw::Text::Text()");

        model = glm::mat4(1.0f);
        this->text = text;
        this->color = color;
        this->origin = origin;

        if (Font::loaded.find(font_path) == Font::loaded.end()) {
            Font::loaded.insert({ font_path, Font(font_path, 96) });
        }
        p_font = &Font::loaded[font_path];

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

    void Text::draw() {
        context.text_shader.use();
        context.text_shader.set_mat4("u_model", model);
        context.text_shader.set_color("u_col", color);
        
        glBindVertexArray(vao);

        int width = get_width(), height = get_height();

        float advance = 0.0f;
        for (char c : text) {
            Glyph g = p_font->glyphs[c];

            float x = g.bearing_x + advance;
            float y = g.bearing_y - g.height;
            float w = g.width;
            float h = g.height;

            if (origin == Origin::BottomMid || origin == Origin::Mid || origin == Origin::TopMid)
                x -= width / 2;
            else if (origin == Origin::BottomRight || origin == Origin::MidRight || origin == Origin::TopRight)
                x -= width;
            
            if (origin == Origin::MidLeft || origin == Origin::Mid || origin == Origin::MidRight)
                y -= height / 2;
            else if (origin == Origin::TopLeft || origin == Origin::TopMid || origin == Origin::TopRight)
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

    int Text::get_width() {
        return p_font->get_str_size(text).x;
    }

    int Text::get_height() {
        return p_font->get_str_size(text).y;
    }

    const std::string& Text::get_text() {
        return text;
    }

    const core::Color& Text::get_color() {
        return color;
    }

}
