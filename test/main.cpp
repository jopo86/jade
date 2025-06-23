#include <iostream>

#include "../src/core.h"
#include "../src/sprite.h"

int main()
{
    jade::Config cfg;
    cfg.width = 800;
    cfg.height = 600;
    cfg.title = "Jade Test Application";
    cfg.background = jade::Color::teal();

    jade::Callbacks cbs;
    cbs.on_update = [](double dt) {
        std::cout << "FPS: " << (1.0 / dt) << std::endl;
    };
    cbs.on_key = [](jade::Key key, jade::InputAction action) {
        if (action != jade::InputAction::Press) return;
        if (key == jade::Key::Esc) {
            jade::terminate();
        } else if (key == jade::Key::Num1) {
            jade::set_wireframe(true);
        }
    };

    jade::init(cfg);

    jade::Sprite smiley("../test/assets/smiley.jpg");
    smiley.translate(0.0f, 0.0f, -1.0f);

    cbs.on_draw = [&smiley]() {
        smiley.draw();
    };

    jade::set_callbacks(cbs);
    jade::run();
    jade::cleanup();
}
