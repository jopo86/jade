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

        void draw() override;

        float width();
        float height();
        const core::Color& get_color();

        void scale_to_width(float width, bool maintain_aspect_ratio = true);
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
