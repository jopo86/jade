#pragma once

#include <string>

#include "color.h"
#include "drawable.h"
#include "font.h"

namespace jade::draw {
    class Text : public Drawable {
    public:
        Text();
        Text(const std::string& text, const std::string& font_path, const core::Color& color = core::Color::black());

        void draw() override;

        void set_text(const std::string& text);
        void set_color(const core::Color& color);

        const std::string& get_text();
        const core::Color& get_color();

    private:
        backend::Font* p_font;
        std::string text;
        core::Color color;
        GLuint vao, vbo;
    };
}
