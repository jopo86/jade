#include "texture.h"
#include "internal.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using jade::internal::allocs;

namespace jade::hidden {
    void err(const std::string&);
    void assert_initialized(const std::string&);
} using jade::hidden::err, jade::hidden::assert_initialized;

namespace jade::backend {

    Texture::Texture() : tex(0) {}

    Texture::Texture(const std::string& filepath) {
        assert_initialized("jade::backend::Texture::Texture()");
        
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        GLsizei n_channels;
        stbi_set_flip_vertically_on_load(true);
        GLubyte* data = stbi_load(filepath.c_str(), &width, &height, &n_channels, 0);
        if (!data) {
            err("jade::backend::Texture::Texture(): failed to load image data from \"" + 
                filepath + ",\" ensure file exists and is a format supported by STB");
            glDeleteTextures(1, &tex);
            return;
        }

        fmt = n_channels == 4 ? GL_RGBA : GL_RGB;

        glTexImage2D(GL_TEXTURE_2D, 0, fmt, width, height, 0, fmt, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        stbi_image_free(data);

        glBindTexture(GL_TEXTURE_2D, 0);

        allocs.texs.push_back(tex);
    }

    void Texture::bind() const {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, tex);
    }
}
