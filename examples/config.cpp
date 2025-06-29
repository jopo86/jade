#include <vector>

#include "../src/prelude.h"

using namespace jade::core;

int main() {

    Config cfg;
    cfg.fps = INT_MAX; // effectively unlock FPS (when vsync off)
    cfg.background = Color::white();
    jade::init(cfg);


    std::vector<Text> texts;
    texts.push_back(Text("Arrows L/R: Change window size", "../examples/assets/lato.ttf", Color::black(), Origin::BottomLeft));
    texts.push_back(Text("Arrows U/D: Change background brightness", "../examples/assets/lato.ttf", Color::black(), Origin::BottomLeft));
    texts.push_back(Text("[V]: Toggle between V-SYNC and unlocked FPS", "../examples/assets/lato.ttf", Color::black(), Origin::BottomLeft));
    texts.push_back(Text("[R]: Toggle resizeable window", "../examples/assets/lato.ttf", Color::black(), Origin::BottomLeft));
    texts.push_back(Text("[Esc]: Quit", "../examples/assets/lato.ttf", Color::black(), Origin::BottomLeft));

    for (int i = 0; i < texts.size(); i++) {
        texts[i].set_position(20, 25 + texts.size() * 30 - 30 * (i + 1), 0.1f);
    }

    Text dims_text("800x600", "../examples/assets/lato.ttf", Color::black(), Origin::BottomRight);
    Text fps_text("FPS: 0", "../examples/assets/lato.ttf", Color::black(), Origin::BottomRight);
    dims_text.set_position(780, 55, 0.1f);
    fps_text.set_position(780, 25, 0.1f);

    Shape text_bg = Shape::rect(780, 20 + texts.size() * 30, Color{ 0.8f, 0.8f, 0.8f }, Origin::BottomLeft);
    text_bg.set_position(10, 10);

    Shape square = Shape::square(100, Color::red());
    square.set_position(400, 350);

    Callbacks cbs;
    cbs.on_key = [&](Key key, Action action) {
        if (action != Action::Press) return;

        if (key == Key::Esc) jade::terminate();
        else if (key == Key::ArrowUp) {
            Color bg = get_config().background;
            if (bg.r >= 1.0f) return;
            bg.r += 0.1f;
            bg.g += 0.1f;
            bg.b += 0.1f;
            set_config_background(bg);
        }
        else if (key == Key::ArrowDown) {
            Color bg = get_config().background;
            if (bg.r <= 0.0f) return;
            bg.r -= 0.1f;
            bg.g -= 0.1f;
            bg.b -= 0.1f;
            set_config_background(bg);
        }
        else if (key == Key::ArrowLeft) {
            set_config_width(get_config().width - 100);
            set_config_height(get_config().height - 100);
            dims_text.set_text(std::to_string(get_config().width) + "x" + std::to_string(get_config().height));
            center_window();
        }
        else if (key == Key::ArrowRight) {
            set_config_width(get_config().width + 100);
            set_config_height(get_config().height + 100);
            dims_text.set_text(std::to_string(get_config().width) + "x" + std::to_string(get_config().height));
            center_window();
        }
        else if (key == Key::V) set_config_vsync(!get_config().vsync);
        else if (key == Key::R) set_config_resizable(!get_config().resizable);
    };
    cbs.on_update = [&](double dt) {
        fps_text.set_text("FPS: " + std::to_string((int)round(1/dt)));
        square.rotate(-45.0f * dt);
    };
    cbs.on_draw = [&]() {
        text_bg.draw();
        for (Text& t : texts) t.draw();
        fps_text.draw();
        dims_text.draw();
        square.draw();
    };

    jade::set_callbacks(cbs);
    jade::run();
}
