#pragma once

#include "drawable.h"
#include "mesh.h"
#include "texture.h"

namespace jade {
    class Sprite : public Drawable {
    public:
        Sprite();
        Sprite(const std::string& image_path);

        void draw() override;

    private:
        Mesh mesh;
        Texture tex;
    };
}
