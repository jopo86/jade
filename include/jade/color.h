#pragma once

namespace jade::core {
    class Color {
    public:
        float r, g, b, a;

        Color() : r(0.0f), g(0.0f), b(0.0f), a(0.0f) {}
        Color(float r, float g, float b, float a = 1.0f)
            : r(r), g(g), b(b), a(a) {}
        
        // (153, 77, 26)
        static inline Color brown() { return Color(0.6f, 0.3f, 0.1f); }
        // (128, 0, 0)
        static inline Color maroon() { return Color(0.5f, 0.0f, 0.0f); }
        // (255, 0, 0)
        static inline Color red() { return Color(1.0f, 0.0f, 0.0f); }
        // (255, 128, 0)
        static inline Color orange() { return Color(1.0f, 0.5f, 0.0f); }
        // (255, 255, 0)
        static inline Color yellow() { return Color(1.0f, 1.0f, 0.0f); }
        // (0, 255, 0)
        static inline Color lime() { return Color(0.0f, 1.0f, 0.0f); }
        // (0, 128, 0)
        static inline Color green() { return Color(0.0f, 0.5f, 0.0f); }
        // (0, 255, 255)
        static inline Color cyan() { return Color(0.0f, 1.0f, 1.0f); }
        // (0, 128, 128)
        static inline Color teal() { return Color(0.0f, 0.5f, 0.5f); }
        // (135, 206, 255)
        static inline Color sky() { return Color(0.53f, 0.81f, 1.0f); }
        // (64, 191, 255)
        static inline Color light_blue() { return Color(0.25f, 0.75f, 1.0f); }
        // (0, 0, 255)
        static inline Color blue() { return Color(0.0f, 0.0f, 1.0f); }
        // (0, 0, 128)
        static inline Color navy() { return Color(0.0f, 0.0f, 0.5f); }
        // (128, 0, 255)
        static inline Color purple() { return Color(0.5f, 0.0f, 1.0f); }
        // (255, 0, 255)
        static inline Color magenta() { return Color(1.0f, 0.0f, 1.0f); }
        // (255, 255, 255)
        static inline Color white() { return Color(1.0f, 1.0f, 1.0f); }
        // (191, 191, 191)
        static inline Color light_gray() { return Color(0.75f, 0.75f, 0.75f); }
        // (128, 128, 128)
        static inline Color gray() { return Color(0.5f, 0.5f, 0.5f); }
        // (64, 64, 64)
        static inline Color dark_gray() { return Color(0.25f, 0.25f, 0.25f); }
        // (0, 0, 0)
        static inline Color black() { return Color(0.0f, 0.0f, 0.0f); }
        // (0, 0, 0, 0)
        static inline Color transparent() { return Color(0.0f, 0.0f, 0.0f, 0.0f); }
    };
}
