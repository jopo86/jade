#pragma once

#include "color.h"
#include "drawable.h"
#include "mesh.h"
#include "defs.h"

namespace jade::draw {
    class Shape : public Drawable {
    public:
        Shape();
        Shape(const backend::Mesh& mesh, float width, float height, const core::Color& color = core::Color::white());

        /*
            @brief Renders the shape to the window.
         !  This should only be called inside the `on_draw` callback.
        */
        void draw() const override;

        // @return The calculated width of the shape, based on its original width and current scale.
        float get_width() const;
        // @return The calculated height of the shape, based on its original height and current scale.
        float get_height() const;
        const core::Color& get_color() const;

        // @brief Changes the scale of the shape so that its width matches the specified value.
        // @param `maintain_aspect_ratio` whether the height will be scaled proportionally.
        void scale_to_width(float width, bool maintain_aspect_ratio = true);
        // @brief Changes the scale of the shape so that its height matches the specified value.
        // @param `maintain_aspect_ratio` whether the width will be scaled proportionally.
        void scale_to_height(float height, bool maintain_aspect_ratio = true);
        void set_color(const core::Color& color);

        static Shape triangle(float side_len);
        static Shape triangle(float side_len, const core::Color& color);
        static Shape triangle(float side_len, core::Origin origin);
        static Shape triangle(float side_len, const core::Color& color, core::Origin origin);

        static Shape triangle(float base, float height);
        static Shape triangle(float base, float height, const core::Color& color);
        static Shape triangle(float base, float height, core::Origin origin);
        static Shape triangle(float base, float height, const core::Color& color, core::Origin origin);

        static Shape square(float side_len);
        static Shape square(float side_len, const core::Color& color);
        static Shape square(float side_len, core::Origin origin);
        static Shape square(float side_len, const core::Color& color, core::Origin origin);

        static Shape rect(float width, float height);
        static Shape rect(float width, float height, const core::Color& color);
        static Shape rect(float width, float height, core::Origin origin);
        static Shape rect(float width, float height, const core::Color& color, core::Origin origin);

        static Shape circle(float radius, int n_segments);
        static Shape circle(float radius, int n_segments, const core::Color& color);
        static Shape circle(float radius, int n_segments, core::Origin origin);
        static Shape circle(float radius, int n_segments, const core::Color& color, core::Origin origin);

    private:
        float init_width, init_height;
        backend::Mesh mesh;
        core::Color color;

        static float xoff(float width, core::Origin origin);
        static float yoff(float height, core::Origin origin);
    };
}
