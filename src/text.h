#pragma once

#include <string>

#include "defs.h"
#include "color.h"
#include "drawable.h"
#include "font.h"

namespace jade::draw {
    class Text : public Drawable {
    public:
        Text();
        Text(const std::string& text, const std::string& font_path);
        Text(const std::string& text, const std::string& font_path, const core::Color& color);
        Text(const std::string& text, const std::string& font_path, core::Origin origin);
        Text(const std::string& text, const std::string& font_path, const core::Color& color, core::Origin origin);

        void draw() override;

        void set_text(const std::string& text);
        void set_color(const core::Color& color);

        int get_width();
        int get_height();
        const std::string& get_text();
        const core::Color& get_color();

    private:
        backend::Font* p_font;
        std::string text;
        core::Color color;
        core::Origin origin;
        GLuint vao, vbo;
    };
}
