#pragma warning(disable: 4244)

#include <vector>
#include <unordered_set>

#include <jade/prelude.h>

using namespace jade::input;

int main() {

    Config cfg;
    cfg.background = Color::white();
    jade::init(cfg);

    std::vector<Text> texts;
    texts.push_back(Text("Keys down IDs: ", "../examples/assets/lato.ttf", 24, Color::black(), Origin::BottomLeft));
    texts.push_back(Text("Mouse buttons down IDs: ", "../examples/assets/lato.ttf", 24, Color::black(), Origin::BottomLeft));
    texts.push_back(Text("[C]: Cycle cursor mode (Normal)", "../examples/assets/lato.ttf", 24, Color::black(), Origin::BottomLeft));
    texts.push_back(Text("Mouse Position: (0, 0)", "../examples/assets/lato.ttf", 24, Color::black(), Origin::BottomLeft));

    for (int i = 0; i < texts.size(); i++) {
        texts[i].set_position(20, 25 + texts.size() * 30 - 30 * (i + 1), 0.1f);
    }

    Shape text_bg = Shape::rect(780, 20 + texts.size() * 30, Color{ 0.8f, 0.8f, 0.8f }, Origin::BottomLeft);
    text_bg.set_position(10, 10);

    std::unordered_set<Key> keys_down;
    std::unordered_set<MouseButton> mbs_down;

    Callbacks cbs;
    cbs.on_key = [&](Key key, Action action) {
        if (key == Key::Esc && action == Action::Press) jade::terminate();
        else if (key == Key::C && action == Action::Press) {
            if (get_cursor_mode() == CursorMode::Normal) {
                set_cursor_mode(CursorMode::Hidden);
                texts[2].set_text("[C]: Cycle cursor mode (Hidden)");
            } else if (get_cursor_mode() == CursorMode::Hidden) {
                set_cursor_mode(CursorMode::Disabled);
                texts[2].set_text("[C]: Cycle cursor mode (Disabled)");
            } else if (get_cursor_mode() == CursorMode::Disabled) {
                set_cursor_mode(CursorMode::Confined);
                texts[2].set_text("[C]: Cycle cursor mode (Confined)");
            } else {
                set_cursor_mode(CursorMode::Normal);
                texts[2].set_text("[C]: Cycle cursor mode (Normal)");
            }
        }

        if (action == Action::Press) keys_down.insert(key);
        else if (action == Action::Release) keys_down.erase(key);

        std::string text_keys = "Keys down IDs: ";
        for (Key k : keys_down) text_keys += std::to_string((int)k) + " ";
        texts[0].set_text(text_keys);
    };
    cbs.on_mouse_button = [&](MouseButton mb, Action action) {
        if (action == Action::Press) mbs_down.insert(mb);
        else if (action == Action::Release) mbs_down.erase(mb);

        std::string text_mbs = "Mouse buttons down IDs: ";
        for (MouseButton m : mbs_down) text_mbs += std::to_string((int)m) + " ";
        texts[1].set_text(text_mbs);
    };
    cbs.on_mouse_moved = [&](double x, double y) {
        texts[3].set_text("Mouse Position: (" + std::to_string((int)x) + ", " + std::to_string((int)y) + ")");
        // could also use input::get_mouse_x() and input::get_mouse_y() in the update callback
    };
    cbs.on_draw = [&]() {
        text_bg.draw();
        for (Text& t : texts) t.draw();
    };

    jade::set_callbacks(cbs);
    jade::run();
}
