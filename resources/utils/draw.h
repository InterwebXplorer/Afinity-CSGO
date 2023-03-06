#pragma once

namespace Draw {
    bool WorldToScreen(const Vector3& WorldPosition, ImVec2& ScreenPosition);
}

namespace UI {
    void Header(const char* label);
    bool CheckBox(const char* label, bool value);
    bool ColorPicker(bool& bShowColorPicker, bool& bShowColorPickerAlt, ImVec4& color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    int Slider(const char* label, int value, int rangemin, int rangemax);
    int DoubleSlider(const char* label, int valuemin, int valuemax, int rangemin, int rangemax);
    bool DropDown(const char* label, const char* items);
    bool DropdownMulti(const char* label, const char* items);
    bool TextBox(const char* label);
    void KeyBind();
    void Console(std::string input);
}