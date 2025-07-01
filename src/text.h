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
        Text(const std::string& text, const std::string& font_path, int font_size);
        Text(const std::string& text, const std::string& font_path, int font_size, const core::Color& color);
        Text(const std::string& text, const std::string& font_path, int font_size, core::Origin origin);
        Text(const std::string& text, const std::string& font_path, int font_size, const core::Color& color, core::Origin origin);

        void draw() const override;

        void set_text(const std::string& text);
        void set_color(const core::Color& color);

        int get_width() const;
        int get_height() const;
        const std::string& get_text() const;
        const core::Color& get_color() const;

    private:
        struct FontKeyHash {
            std::size_t operator()(const std::pair<std::string, int>& key) const {
                std::hash<std::string> hash_str;
                std::hash<int> hash_int;
                return hash_str(key.first) ^ (hash_int(key.second) << 1);
            }
        };
        static std::unordered_map<std::pair<std::string, int>, backend::Font, FontKeyHash> loaded_fonts;

        backend::Font* p_font;
        std::string text;
        core::Color color;
        core::Origin origin;
        GLuint vao, vbo;
    };
}
