#include <iostream>

#include "../src/prelude.h"

const float CAM_SPEED = 500.0f;

int main()
{
    jade::init();

    Sprite smiley("../test/assets/smiley.jpg");
    smiley.translate(250, 300);
    smiley.scale(0.2f);

    Shape circle = Shape::circle(100, 6, Color::blue());
    circle.translate(550, 300);

    Callbacks cbs;
    cbs.on_update = [&](double dt) {
        if (is_key_down(Key::Esc)) jade::terminate();
        circle.rotate(-45.0f * dt);
    };
    cbs.on_draw = [&]() {
        smiley.draw();
        circle.draw();
    };

    jade::set_callbacks(cbs);
    jade::run();
}
