#include <jade/font.h>
#include <jade/internal.h>

namespace jade::hidden {
    void err(const std::string&);
    void assert_initialized(const std::string&);
} using jade::hidden::err, jade::hidden::assert_initialized;

using jade::internal::context;

namespace jade::backend {

    Font::Font() : face(nullptr) {}

    Font::Font(const std::string& path, unsigned int px) {
        assert_initialized("jade::backend::Font::Font()");

        if (FT_New_Face(context.ft, path.c_str(), 0, &face)) {
            err("jade::backend::Font::Font(): failed to load font \"" + path + "\"");
            exit(EXIT_FAILURE);
        }

        FT_Set_Pixel_Sizes(face, 0, px);

        glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

        for (unsigned char c = 0; c < 128; c++) {

            if (FT_Load_Char(face, c, FT_LOAD_RENDER)) {
                err("jade::backend::Font::Font(): failed to load glyph '" + std::to_string(c) + "'");
                continue;
            }

            GLuint tex;
            glGenTextures(1, &tex);
            glBindTexture(GL_TEXTURE_2D, tex);
            glTexImage2D(
                GL_TEXTURE_2D, 0, GL_RED,
                face->glyph->bitmap.width,
                face->glyph->bitmap.rows,
                0, GL_RED, GL_UNSIGNED_BYTE,
                face->glyph->bitmap.buffer
            );
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

            Glyph glyph {
                tex,
                (int)face->glyph->bitmap.width, (int)face->glyph->bitmap.rows,
                face->glyph->bitmap_left, face->glyph->bitmap_top,
                (unsigned int)face->glyph->advance.x >> 6
            };
            glyphs.insert({ c, glyph });
            
            internal::allocs.texs.push_back(tex);
        }
        glBindTexture(GL_TEXTURE_2D, 0);
        internal::allocs.faces.push_back(face);
    }

    glm::ivec2 Font::get_str_size(const std::string& str) {
        glm::ivec2 size(0.0f, glyphs['A'].height);
        for (int i = 0; i < str.size(); i++) {
            Glyph g = glyphs[str[i]];
            if (i < str.size() - 1) size.x += g.advance;
            else size.x += g.bearing_x + g.width;
        }
        return size;
    }
}
