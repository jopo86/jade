#pragma once

#include "color.h"
#include "drawable.h"
#include "mesh.h"

namespace jade::draw {
    class Shape : public Drawable {
    public:
        Shape();
        Shape(const backend::Mesh& mesh, const core::Color& color = core::Color::black());

        void draw() override;

        void set_color(const core::Color& color);
        const core::Color& get_color();

        static Shape triangle(float side_len, const core::Color& color = core::Color::black());
        static Shape triangle(float base, float height, const core::Color& color = core::Color::black());
        static Shape square(float side_len, const core::Color& color = core::Color::black());
        static Shape quad(float width, float height, const core::Color& color = core::Color::black());
        static Shape circle(float radius, int n_segments, const core::Color& color = core::Color::black());

    private:
        backend::Mesh mesh;
        core::Color color;
    };
}
