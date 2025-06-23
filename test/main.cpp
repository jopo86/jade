#include <iostream>

#include "../src/jade.h"
#include "../src/sprite.h"

const float CAM_SPEED = 500.0f;

int main()
{
    jade::core::init();

    jade::Sprite smiley("../test/assets/smiley.jpg");

    jade::Callbacks cbs;
    cbs.on_draw = [&smiley]() {
        smiley.draw();
    };
    cbs.on_update = [](double dt) {
        if (jade::input::is_key_down(jade::Key::W)) jade::camera::translate(0.0f, CAM_SPEED * dt);
        if (jade::input::is_key_down(jade::Key::A)) jade::camera::translate(-CAM_SPEED * dt, 0.0f);
        if (jade::input::is_key_down(jade::Key::S)) jade::camera::translate(0.0f, -CAM_SPEED * dt);
        if (jade::input::is_key_down(jade::Key::D)) jade::camera::translate(CAM_SPEED * dt, 0.0f);
        if (jade::input::is_key_down(jade::Key::Esc)) jade::core::terminate();
    };

    jade::core::set_callbacks(cbs);
    jade::core::run();
    jade::core::cleanup();
}
