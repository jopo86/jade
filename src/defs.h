#pragma once

#include <glad/glad.h>
#include <glfw/glfw3.h>

namespace jade::core {
    enum class Origin {
        Mid,
        BottomLeft,
        Bottom,
        BottomRight,
        Right,
        TopRight,
        Top,
        TopLeft,
        Left,
    };
}

namespace jade::draw {
    enum class DrawMode {
        Normal = GL_FILL,
        Wireframe = GL_LINE,
        Points = GL_POINT,
    };
}

namespace jade::input {
    enum class CursorMode {
        Normal = GLFW_CURSOR_NORMAL,
        Hidden = GLFW_CURSOR_HIDDEN,
        Disabled = GLFW_CURSOR_DISABLED,
        Confined = GLFW_CURSOR_CAPTURED,
    };

    enum class Action {
        Null = -1,
        Release = GLFW_RELEASE,
        Press = GLFW_PRESS,
        Repeat = GLFW_REPEAT,
    };

    enum class Key {
        Null = 0,
        Unknown = -1,
        Space = GLFW_KEY_SPACE,
        Apostrophe = GLFW_KEY_APOSTROPHE,
        Comma = GLFW_KEY_COMMA,
        Minus = GLFW_KEY_MINUS,
        Period = GLFW_KEY_PERIOD,
        Slash = GLFW_KEY_SLASH,
        Num0 = GLFW_KEY_0,
        Num1 = GLFW_KEY_1,
        Num2 = GLFW_KEY_2,
        Num3 = GLFW_KEY_3,
        Num4 = GLFW_KEY_4,
        Num5 = GLFW_KEY_5,
        Num6 = GLFW_KEY_6,
        Num7 = GLFW_KEY_7,
        Num8 = GLFW_KEY_8,
        Num9 = GLFW_KEY_9,
        Semicolon = GLFW_KEY_SEMICOLON,
        Equal = GLFW_KEY_EQUAL,
        A = GLFW_KEY_A,
        B = GLFW_KEY_B,
        C = GLFW_KEY_C,
        D = GLFW_KEY_D,
        E = GLFW_KEY_E,
        F = GLFW_KEY_F,
        G = GLFW_KEY_G,
        H = GLFW_KEY_H,
        I = GLFW_KEY_I,
        J = GLFW_KEY_J,
        K = GLFW_KEY_K,
        L = GLFW_KEY_L,
        M = GLFW_KEY_M,
        N = GLFW_KEY_N,
        O = GLFW_KEY_O,
        P = GLFW_KEY_P,
        Q = GLFW_KEY_Q,
        R = GLFW_KEY_R,
        S = GLFW_KEY_S,
        T = GLFW_KEY_T,
        U = GLFW_KEY_U,
        V = GLFW_KEY_V,
        W = GLFW_KEY_W,
        X = GLFW_KEY_X,
        Y = GLFW_KEY_Y,
        Z = GLFW_KEY_Z,
        LeftBracket = GLFW_KEY_LEFT_BRACKET,
        Backslash = GLFW_KEY_BACKSLASH,
        RightBracket = GLFW_KEY_RIGHT_BRACKET,
        GraveAccent = GLFW_KEY_GRAVE_ACCENT,
        World1 = GLFW_KEY_WORLD_1,
        World2 = GLFW_KEY_WORLD_2,
        Escape = GLFW_KEY_ESCAPE,
        Enter = GLFW_KEY_ENTER,
        Tab = GLFW_KEY_TAB,
        Backspace = GLFW_KEY_BACKSPACE,
        Insert = GLFW_KEY_INSERT,
        Delete = GLFW_KEY_DELETE,
        ArrowRight = GLFW_KEY_RIGHT,
        ArrowLeft = GLFW_KEY_LEFT,
        ArrowDown = GLFW_KEY_DOWN,
        ArrowUp = GLFW_KEY_UP,
        PageUp = GLFW_KEY_PAGE_UP,
        PageDown = GLFW_KEY_PAGE_DOWN,
        Home = GLFW_KEY_HOME,
        End = GLFW_KEY_END,
        CapsLock = GLFW_KEY_CAPS_LOCK,
        ScrollLock = GLFW_KEY_SCROLL_LOCK,
        NumLock = GLFW_KEY_NUM_LOCK,
        PrintScreen = GLFW_KEY_PRINT_SCREEN,
        Pause = GLFW_KEY_PAUSE,
        F1 = GLFW_KEY_F1,
        F2 = GLFW_KEY_F2,
        F3 = GLFW_KEY_F3,
        F4 = GLFW_KEY_F4,
        F5 = GLFW_KEY_F5,
        F6 = GLFW_KEY_F6,
        F7 = GLFW_KEY_F7,
        F8 = GLFW_KEY_F8,
        F9 = GLFW_KEY_F9,
        F10 = GLFW_KEY_F10,
        F11 = GLFW_KEY_F11,
        F12 = GLFW_KEY_F12,
        F13 = GLFW_KEY_F13,
        F14 = GLFW_KEY_F14,
        F15 = GLFW_KEY_F15,
        F16 = GLFW_KEY_F16,
        F17 = GLFW_KEY_F17,
        F18 = GLFW_KEY_F18,
        F19 = GLFW_KEY_F19,
        F20 = GLFW_KEY_F20,
        F21 = GLFW_KEY_F21,
        F22 = GLFW_KEY_F22,
        F23 = GLFW_KEY_F23,
        F24 = GLFW_KEY_F24,
        F25 = GLFW_KEY_F25,
        Numpad0 = GLFW_KEY_KP_0,
        Numpad1 = GLFW_KEY_KP_1,
        Numpad2 = GLFW_KEY_KP_2,
        Numpad3 = GLFW_KEY_KP_3,
        Numpad4 = GLFW_KEY_KP_4,
        Numpad5 = GLFW_KEY_KP_5,
        Numpad6 = GLFW_KEY_KP_6,
        Numpad7 = GLFW_KEY_KP_7,
        Numpad8 = GLFW_KEY_KP_8,
        Numpad9 = GLFW_KEY_KP_9,
        NumpadDecimal = GLFW_KEY_KP_DECIMAL,
        NumpadDivide = GLFW_KEY_KP_DIVIDE,
        NumpadMultiply = GLFW_KEY_KP_MULTIPLY,
        NumpadSubtract = GLFW_KEY_KP_SUBTRACT,
        NumpadAdd = GLFW_KEY_KP_ADD,
        NumpadEnter = GLFW_KEY_KP_ENTER,
        NumpadEqual = GLFW_KEY_KP_EQUAL,
        LeftShift = GLFW_KEY_LEFT_SHIFT,
        LeftControl = GLFW_KEY_LEFT_CONTROL,
        LeftAlt = GLFW_KEY_LEFT_ALT,
        LeftSuper = GLFW_KEY_LEFT_SUPER,
        RightShift = GLFW_KEY_RIGHT_SHIFT,
        RightControl = GLFW_KEY_RIGHT_CONTROL,
        RightAlt = GLFW_KEY_RIGHT_ALT,
        RightSuper = GLFW_KEY_RIGHT_SUPER,
        Menu = GLFW_KEY_MENU,

        Application = Menu, 			// @brief Alias for `Key::Menu`
        App = Menu, 					// @brief Alias for `Key::Menu`

        Esc = Escape, 					// @brief Alias for `Key::Escape`
        Return = Enter, 				// @brief Alias for `Key::Enter`

        LCtrl = LeftControl, 			// @brief Alias for `Key::LeftControl`
        RCtrl = RightControl, 			// @brief Alias for `Key::RightControl`
        LShift = LeftShift, 			// @brief Alias for `Key::LeftShift`
        RShift = RightShift, 			// @brief Alias for `Key::RightShift`
        LAlt = LeftAlt, 				// @brief Alias for `Key::LeftAlt`
        RAlt = RightAlt, 				// @brief Alias for `Key::RightAlt`
        LSuper = LeftSuper, 			// @brief Alias for `Key::LeftSuper`
        RSuper = RightSuper, 			// @brief Alias for `Key::RightSuper`
        LeftCommand = LeftSuper, 		// @brief Alias for `Key::LeftSuper`
        RightCommand = RightSuper, 		// @brief Alias for `Key::RightSuper`
        LCmd = LeftSuper, 				// @brief Alias for `Key::LeftSuper`
        RCmd = RightSuper, 				// @brief Alias for `Key::RightSuper`
        LeftWindows = LeftSuper, 		// @brief Alias for `Key::LeftSuper`
        RightWindows = RightSuper, 		// @brief Alias for `Key::RightSuper`
        LWin = LeftSuper, 				// @brief Alias for `Key::LeftSuper`
        RWin = RightSuper, 				// @brief Alias for `Key::RightSuper`
        Windows = LeftSuper, 			// @brief Alias for `Key::LeftSuper`
        Win = LeftSuper, 				// @brief Alias for `Key::LeftSuper`

        PrtSc = PrintScreen, 			// @brief Alias for `Key::PrintScreen`
        Ins = Insert, 					// @brief Alias for `Key::Insert`
        PgUp = PageUp, 					// @brief Alias for `Key::PageUp`
        PgDn = PageDown, 				// @brief Alias for `Key::PageDown`
        Del = Delete, 					// @brief Alias for `Key::Delete`

        Up = ArrowUp, 					// @brief Alias for `Key::ArrowUp`
        Down = ArrowDown, 				// @brief Alias for `Key::ArrowDown`
        Left = ArrowLeft, 				// @brief Alias for `Key::ArrowLeft`
        Right = ArrowRight, 			// @brief Alias for `Key::ArrowRight`

        MaxKey = Menu,
    };

    enum class MouseButton {
        Null = -2,
        Unknown = -1,
        Button1 = GLFW_MOUSE_BUTTON_1,
        Button2 = GLFW_MOUSE_BUTTON_2,
        Button3 = GLFW_MOUSE_BUTTON_3,
        Button4 = GLFW_MOUSE_BUTTON_4,
        Button5 = GLFW_MOUSE_BUTTON_5,
        Button6 = GLFW_MOUSE_BUTTON_6,
        Button7 = GLFW_MOUSE_BUTTON_7,
        Button8 = GLFW_MOUSE_BUTTON_8,

        Left = Button1, 				// @brief Alias for `MouseButton::Button1`
        Right = Button2, 				// @brief Alias for `MouseButton::Button2`
        Middle = Button3, 				// @brief Alias for `MouseButton::Button3`
        SideBack = Button4, 			// @brief Alias for `MouseButton::Button4`
        SideFront = Button5, 			// @brief Alias for `MouseButton::Button5`

        MaxButton = Button8
    };
}
