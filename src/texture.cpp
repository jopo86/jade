#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace jade {
    void err(const std::string&);
}

jade::Texture::Texture() : tex(0) {}

jade::Texture::Texture(const std::string& filepath) {
    glGenTextures(1, &tex);
    glBindTexture(GL_TEXTURE_2D, tex);

    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTextureParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    GLsizei n_channels;
    stbi_set_flip_vertically_on_load(true);
    GLubyte* data = stbi_load(filepath.c_str(), &width, &height, &n_channels, 0);
    if (!data) {
        err("jade::Texture::Texture(): failed to load image data from \"" + 
            filepath + ",\" ensure file exists and is a format supported by STB");
        return;
    }

    fmt = n_channels == 4 ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, fmt, width, height, 0, fmt, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(data);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void jade::Texture::bind() {
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, tex);
}
