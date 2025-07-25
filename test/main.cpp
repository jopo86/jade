#include <iostream>

#include "../src/prelude.h"

int main()
{
    jade::init();

    Sprite smiley("../test/assets/smiley.jpg");
    smiley.translate(250, 300);
    smiley.scale(0.2f);

    Shape circle = Shape::circle(100, 6, Color::blue());
    circle.translate(550, 300);

    Text text("hello world", "../test/assets/arial.ttf", Color::red(), Origin::BottomRight);
    text.translate(800, 0, 0.1f);

    Callbacks cbs;
    cbs.on_update = [&](double dt) {
        if (is_key_down(Key::Esc)) jade::terminate();
        circle.rotate(-45.0f * dt);
        // text.set_text("FPS: " + std::to_string((int)round(1/dt)));
    };
    cbs.on_draw = [&]() {
        smiley.draw();
        circle.draw();
        text.draw();
    };

    jade::set_callbacks(cbs);
    jade::run();
}
