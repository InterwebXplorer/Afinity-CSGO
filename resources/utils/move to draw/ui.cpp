#include "../imgui/imgui.h"
#include "../imgui/imgui_freetype.h"
#include "../imgui/imgui_internal.h"
#include "../imgui/impl/imgui_impl_dx9.h"
#include "../imgui/impl/imgui_impl_win32.h"

void Header(const char* label) { // -------Group-------
    
};

bool CheckBox(const char* label, bool value) {

};

bool ColorPicker(bool& bShowColorPicker, bool& bShowColorPickerAlt) {
// if right clicked popup copy/paste popup

    if (ImGui::IsItemClicked(0)) {
        //render color picker
    }

    if (ImGui::IsItemClicked(1)) {
        const char* ColorPickerOptions[] = {"Copy", "Paste"}
    }
};

int Slider(const char* label, int value, int rangemin, int rangemax) {
    ImGuiWindow* window = ImGui::GetCurrentWindow();
    if (window->SkipItems())
        return;

//ee
    ImGuiContext& g = *GImGui;
    const ImGuiStyle& style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = CalcTextSize(label, NULL, true);

    //ahhhhhhhhhhhh idk
};

int DoubleSlider(const char* label, int valuemin, int valuemax, int rangemin, int rangemax) {

};

bool DropDown(const char* label, const char* items) {


    if (ImGui::IsItemClicked(0)) {
        //render dropdown menu
    }
};

bool DropdownMulti(const char* label, const char* items) {


    if (ImGui::IsItemClicked(0)) {
        //render dropdown menu
    }
};

bool TextBox(const char* label) {

};

void KeyBind() { // [-]
    const char* KeyBindSelectedKeyDisplay[] = {};


    if (ImGui::IsItemClicked(1)) {
        const char* KeyBindOptions[] = {"Always", "Toggle", "On Hold", "Off Hold"};
    }
};