#include <iostream>

#include "../src/core.h"
#include "../src/mesh.h"

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
        if (key == jade::Key::Esc && action == jade::InputAction::Press) {
            jade::terminate();
        }
    };

    jade::init(cfg);

    jade::Mesh mesh = jade::Mesh::square(1.0f, false);

    cbs.on_draw = [&mesh]() {
        mesh.draw();
    };

    jade::set_callbacks(cbs);
    jade::run();
    jade::cleanup();
}
