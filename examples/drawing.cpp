#pragma warning(disable: 4244)

#include <iostream>

#include <jade/prelude.h>

int main()
{
    jade::init();

    Sprite smiley("../examples/assets/smiley.jpg");
    smiley.set_position(250, 375);
    smiley.scale_to_width(200);

    Shape hex = Shape::circle(100, 6, Color::blue());
    hex.set_position(550, 375);

    Text text("hello world", "../examples/assets/lato.ttf", 96,  Color::red());
    text.set_position(400, 175, 0.1f);

    Callbacks cbs;
    cbs.on_update = [&](float dt) {
        hex.rotate(-45.0f * dt); // 45 deg/sec
    };
    cbs.on_draw = [&]() {
        smiley.draw();
        hex.draw();
        text.draw();
    };

    jade::set_callbacks(cbs);
    jade::run();
}
