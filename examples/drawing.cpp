#include <iostream>

#include "../src/prelude.h"

int main()
{
    jade::init();

    Sprite smiley("../examples/assets/smiley.jpg");
    smiley.set_position(250, 375);
    smiley.scale_to_width(200);

    Shape circle = Shape::circle(100, 6, Color::blue());
    circle.set_position(550, 375);

    Text text("hello world", "../examples/assets/lato.ttf",  Color::red());
    text.set_position(400, 175, 0.1f);

    Callbacks cbs;
    cbs.on_draw = [&]() {
        smiley.draw();
        circle.draw();
        text.draw();
    };

    jade::set_callbacks(cbs);
    jade::run();
}
