#pragma once

namespace Draw {
    bool WorldToScreen(const Vector3& WorldPosition, ImVec2& ScreenPosition);
}

namespace KeyArray {
    const char* KeyNames[] = {
        "OFF", "M1", "M2", "Cancel", "M3", "M4", "M5", "UNK",
        "Back", "Tab", "UNK", "UNK", "Clear", "Return", "UNK", "UNK", "Shift", "CTRL", "ALT", "Pause",
        "Capital", "Kana", "UNK", "Junja", "Final", "Kanji", "UNK", "ESC", "Convert", "Nonconvert", "Accept",
        "Modechange", "Space","Prior", "Next", "End", "Home", "Left", "Up", "Right", "Down", "Select", "Print", "Execute",
        "Snapshot", "Insert", "Delete", "Help", "0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "UNK", "UNK",
        "UNK", "UNK", "UNK", "UNK", "UNK", "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K",
        "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "Left Win", "Rigth Win", "Apps",
        "UNK", "Sleep", "N0", "N1", "N2", "N3", "N4", "N5", "N6", "N7", "N8", "N9",
        "Mutiply", "Add", "Separator", "Subtract", "Decimal", "Divide", "F1", "F2", "F3", "F4", "F5", "F6", "F7", "F8",
        "F9", "F10", "F11", "F12", "F13", "F14", "F15", "F16", "F17", "F18", "F19", "F20", "F21", "F22", "F23", "F24",
        "UNK", "UNK", "UNK", "UNK", "UNK", "UNK", "UNK", "UNK", "Num Lock", "Scrool",
        "Equal", "Masshou", "Touroku", "Loya", "Roya", "UNK", "UNK", "UNK", "UNK", "UNK", "UNK",
        "UNK", "UNK", "UNK", " LShift", "RShift", "LCTRL", "RCTRL", "LALT", "RALT"
    };
}

namespace UI {
    void Header(const char* label);
    bool CheckBox(const char* Label, bool Value);
    void ColorPicker(bool& ShowColorPicker, bool& ShowColorPickerAlt, ImVec4& Color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
}