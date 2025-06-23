#include "sprite.h"

#include "jade.h"

namespace jade::hidden {
    void assert_initialized(const std::string&);
} using jade::hidden::assert_initialized;

jade::Sprite::Sprite() {
    model = glm::mat4(1.0f);
}

jade::Sprite::Sprite(const std::string& path) {
    assert_initialized("jade::Sprite::Sprite()");
    
    model = glm::mat4(1.0f);
    tex = Texture(path);
    mesh = Mesh::quad(tex.width, tex.height, true);
}

void jade::Sprite::draw() {
    context.sprite_shader.use();
    context.sprite_shader.set_mat4("u_model", model);
    tex.bind();
    mesh.draw();
}
