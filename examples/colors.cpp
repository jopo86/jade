#pragma warning(disable: 4244)

#include <iostream>

#include "../src/prelude.h"

int main()
{
    Config cfg;
    cfg.width = 1200;
    cfg.height = 1000;
    cfg.background = Color(0.1f, 0.1f, 0.1f);
    jade::init(cfg);

    Color colors[] = {
        Color::brown(),
        Color::maroon(),
        Color::red(),
        Color::orange(),
        Color::yellow(),
        Color::lime(),
        Color::green(),
        Color::cyan(),
        Color::teal(),
        Color::sky(),
        Color::light_blue(),
        Color::blue(),
        Color::navy(),
        Color::purple(),
        Color::magenta(),
        Color::white(),
        Color::light_gray(),
        Color::gray(),
        Color::dark_gray(),
        Color::black(),
    };

    Shape circle = Shape::circle(75, 50);

    Callbacks cbs;
    cbs.on_draw = [&]() {
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 5; j++) {
                circle.set_position(175 + 200 * j, 1000 - 175 - 200 * i);
                circle.set_color(colors[j + i * 5]);
                circle.draw();
            }
        }
    };

    jade::set_callbacks(cbs);
    jade::run();
}
