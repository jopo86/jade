#include <iostream>

#include "../src/core.h"

int main()
{
    jade::Config cfg;
    cfg.width = 1920;
    cfg.height = 1080;
    cfg.title = "Jade Test Application";
    cfg.background = jade::Color::teal();

    jade::Callbacks cbs;
    cbs.on_update = [](double dt) {
        std::cout << "FPS: " << (1.0 / dt) << std::endl;
    };
    cbs.on_key = [](jade::Key key, jade::InputAction action) {
        if (key == jade::Key::Escape && action == jade::InputAction::Press) {
            jade::terminate();
        }
    };

    jade::init(cfg, cbs);
    jade::run();
}
