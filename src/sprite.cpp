#include "sprite.h"

#include "internal.h"

namespace jade::hidden {
    void assert_initialized(const std::string&);
} using jade::hidden::assert_initialized;

using jade::backend::Mesh, jade::backend::Texture;
using jade::internal::context;

namespace jade::draw {
    
    Sprite::Sprite() {
        model = glm::mat4(1.0f);
    }

    Sprite::Sprite(const std::string& path) {
        assert_initialized("jade::draw::Sprite::Sprite()");
        
        model = glm::mat4(1.0f);
        tex = Texture(path);
        mesh = Mesh::quad(tex.width, tex.height, true);
    }

    void Sprite::draw() {
        context.sprite_shader.use();
        context.sprite_shader.set_mat4("u_model", model);
        tex.bind();
        mesh.draw();
    }
}
