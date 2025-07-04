#pragma once

#include "defs.h"
#include "drawable.h"
#include "mesh.h"
#include "texture.h"

namespace jade::draw {
    class Sprite : public Drawable {
    public:
        Sprite();
        Sprite(const std::string& image_path, core::Origin origin = core::Origin::Center);

        /*
            @brief Renders the sprite to the window.
         !  This should only be called inside the `on_draw` callback.
        */
        void draw() const override;

        // @return The calculated width of the sprite, based on its original width and current scale.
        float get_width() const;
        // @return The calculated height of the sprite, based on its original height and current scale.
        float get_height() const;
        
        // @brief Changes the scale of the sprite so that its width matches the specified value.
        // @param `maintain_aspect_ratio` whether the height will be scaled proportionally.
        void scale_to_width(float width, bool maintain_aspect_ratio = true);
        // @brief Changes the scale of the sprite so that its height matches the specified value.
        // @param `maintain_aspect_ratio` whether the width will be scaled proportionally.
        void scale_to_height(float height, bool maintain_aspect_ratio = true);

    private:
        float init_width, init_height;
        backend::Mesh mesh;
        backend::Texture tex;
    };
}
