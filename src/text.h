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

        /*
            @brief Renders the text to the window.
         !  This should only be called inside the `on_draw` callback.
        */
        void draw() const override;

        // @return The calculated width of the text, based on its original width and current scale.
        int get_width() const;
        // @return The calculated height of the text, based on its original height and current scale.
        int get_height() const;
        const std::string& get_text() const;
        const core::Color& get_color() const;

        void set_text(const std::string& text);
        void set_color(const core::Color& color);

        // @brief Changes the scale of the text so that its width matches the specified value.
        // @param `maintain_aspect_ratio` whether the height will be scaled proportionally.
        void scale_to_width(float width, bool maintain_aspect_ratio = true);
        // @brief Changes the scale of the text so that its height matches the specified value.
        // @param `maintain_aspect_ratio` whether the width will be scaled proportionally.
        void scale_to_height(float height, bool maintain_aspect_ratio = true);

    private:
        struct FontKeyHash {
            std::size_t operator()(const std::pair<std::string, int>& key) const {
                std::hash<std::string> hash_str;
                std::hash<int> hash_int;
                return hash_str(key.first) ^ (hash_int(key.second) << 1);
            }
        };
        static std::unordered_map<std::pair<std::string, int>, backend::Font, FontKeyHash> loaded_fonts;

        float init_width, init_height;
        backend::Font* p_font;
        std::string text;
        core::Color color;
        core::Origin origin;
        GLuint vao, vbo;
    };
}
