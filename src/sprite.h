#pragma once

#include "defs.h"
#include "drawable.h"
#include "mesh.h"
#include "texture.h"

namespace jade::draw {
    class Sprite : public Drawable {
    public:
        Sprite();
        Sprite(const std::string& image_path, core::Origin origin = core::Origin::Mid);

        void draw() override;

        float width();
        float height();
        
        void scale_to_width(float width, bool maintain_aspect_ratio = true);
        void scale_to_height(float height, bool maintain_aspect_ratio = true);

    private:
        float init_width, init_height;
        backend::Mesh mesh;
        backend::Texture tex;
    };
}
