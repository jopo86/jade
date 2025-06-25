#pragma once

namespace jade::core {
    class Color {
    public:
        float r, g, b, a;

        Color() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {}
        Color(float r, float g, float b, float a = 1.0f)
            : r(r), g(g), b(b), a(a) {}
        
        static inline Color red() { return Color(1.0f, 0.0f, 0.0f); }
        static inline Color orange() { return Color(1.0f, 0.5f, 0.0f); }
        static inline Color yellow() { return Color(1.0f, 1.0f, 0.0f); }
        static inline Color lime() { return Color(0.5f, 1.0f, 0.0f); }
        static inline Color green() { return Color(0.0f, 1.0f, 0.0f); }
        static inline Color cyan() { return Color(0.0f, 1.0f, 1.0f); }
        static inline Color teal() { return Color(0.0f, 0.5f, 0.5f); }
        static inline Color blue() { return Color(0.0f, 0.0f, 1.0f); }
        static inline Color purple() { return Color(0.5f, 0.0f, 1.0f); }
        static inline Color magenta() { return Color(1.0f, 0.0f, 1.0f); }
        static inline Color white() { return Color(1.0f, 1.0f, 1.0f); }
        static inline Color black() { return Color(0.0f, 0.0f, 0.0f); }
        static inline Color gray() { return Color(0.5f, 0.5f, 0.5f); }
        static inline Color transparent() { return Color(0.0f, 0.0f, 0.0f, 0.0f); }
        static inline Color brown() { return Color(0.6f, 0.3f, 0.1f); }
    };
}
