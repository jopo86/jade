#pragma once

#include <unordered_map>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace jade::backend {

    struct Glyph {
        GLuint tex;
        int width, height;
        int bearing_x, bearing_y;
        unsigned int advance;
    };

    class Font {
    public:
        Font();
        Font(const std::string& path, unsigned int px);

        glm::ivec2 get_str_size(const std::string& str);

        std::unordered_map<char, Glyph> glyphs;

    private:
        FT_Face face;
    };
}
