#pragma warning(disable: 4244 4081 4305)

#include <vector>
#include <ctime>

#include "../src/prelude.h"

using jade::input::is_key_down;

const int DROP_SPEED = 300; // raindrops fall at 300 px/sec
const int BUCKET_SPEED = 600; // bucket moves at 600 px/sec

const int BUCKET_WIDTH = 150;
const int DROP_WIDTH = 25;

struct Pos {
    int x, y;
};

int main() {

    srand(time(nullptr));

    Config cfg;
    cfg.width = cfg.height = 1024;
    cfg.title = "Raindrop Catch";

    jade::init(cfg);

    Sprite background("../examples/assets/background.png", Origin::BottomLeft);
    background.set_z(-0.1);

    Sprite bucket("../examples/assets/bucket.png", Origin::Bottom);
    bucket.scale_to_width(BUCKET_WIDTH);
    bucket.set_position(512, 50);

    Sprite raindrop("../examples/assets/raindrop.png", Origin::Top);
    raindrop.scale_to_width(DROP_WIDTH);
    raindrop.set_z(0.1);

    Text score_text("Score: 0", "../examples/assets/lato.ttf", 48, Origin::TopLeft);
    score_text.set_position(20, 1024 - 20);

    std::vector<Pos> raindrops;

    int score = 0;
    float spawn_interval = 1.0f; // raindrops spawn every 1 second 
    float spawn_timer = spawn_interval;

    Callbacks cbs;
    cbs.on_update = [&](double dt) {
        spawn_timer -= dt;
        if (spawn_timer <= 0) {
            spawn_timer = spawn_interval + spawn_timer;
            raindrops.push_back(Pos{ rand() % 1024, 1024 });
            if (spawn_interval >= 0.3f) spawn_interval -= 0.01f; // raindrops spawn faster each second
        }
        for (auto it = raindrops.begin(); it != raindrops.end();) {
            if (
                // the collision math here is a little wacky because of the different origins
                it->x + raindrop.width() / 2 >= bucket.get_x() - bucket.width() / 2 &&
                it->x - raindrop.width() / 2 <= bucket.get_x() + bucket.width() / 2 &&
                it->y - raindrop.height() <= bucket.get_y() + bucket.height() * 0.85 &&
                it->y >= bucket.get_y() + bucket.height() * 0.8
            ) {
                score++;
                score_text.set_text("Score: " + std::to_string(score));
                it = raindrops.erase(it);
            }
            else if (it->y <= 0) it = raindrops.erase(it);
            else {
                it->y -= DROP_SPEED * dt;
                it++;
            }
        }

        if (is_key_down(Key::ArrowLeft) || is_key_down(Key::A)) bucket.translate(-BUCKET_SPEED * dt, 0);
        if (is_key_down(Key::ArrowRight) || is_key_down(Key::D)) bucket.translate(BUCKET_SPEED * dt, 0);
        if (bucket.get_x() < 0) bucket.set_x(0);
        else if (bucket.get_x() > 1024) bucket.set_x(1024);

        if (is_key_down(Key::Esc)) jade::terminate();
    };
    cbs.on_draw = [&]() {
        background.draw();
        bucket.draw();
        for (const Pos& p : raindrops) {
            raindrop.set_position(p.x, p.y);
            raindrop.draw();
        }
        score_text.draw();
    };

    jade::set_callbacks(cbs);
    jade::run();
}
