#pragma once

#include "jade.h"
#include "sprite.h"
#include "shape.h"
#include "text.h"

namespace jade {
    using core::init;
    using core::run;
    using core::set_callbacks;
    using core::terminate;
}

using jade::core::Config;
using jade::core::Callbacks;
using jade::core::Color;
using jade::core::Origin;

using jade::draw::Shape;
using jade::draw::Sprite;
using jade::draw::Text;

using jade::input::Key;
using jade::input::MouseButton;
using jade::input::Action;
