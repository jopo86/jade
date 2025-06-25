#pragma once

#include <string>

#include "drawable.h"

namespace jade::draw {
    class Text : public Drawable {
    public:
        Text();
        Text(const std::string& text);
    };
}
