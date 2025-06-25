#pragma once

#include "drawable.h"
#include "mesh.h"
#include "texture.h"

namespace jade::draw {
    class Sprite : public Drawable {
    public:
        Sprite();
        Sprite(const std::string& image_path);

        void draw() override;

    private:
        backend::Mesh mesh;
        backend::Texture tex;
    };
}
