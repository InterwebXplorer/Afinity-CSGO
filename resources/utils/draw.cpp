#include "../imgui/imgui.h"
#include "../imgui/imgui_freetype.h"
#include "../imgui/imgui_internal.h"
#include "../imgui/impl/imgui_impl_dx9.h"
#include "../imgui/impl/imgui_impl_win32.h"
#include "vector.h"
#include "draw.h"

bool Draw::WorldToScreen(const Vector3& WorldPosition, ImVec2& ScreenPosition) {
    const ViewMatrix_t& WorldToScreen = I::Engine->WorldToScreenMatrix();
	const float Width = WorldToScreen[3][0] * WorldPosition.x + WorldToScreen[3][1] * WorldPosition.y + WorldToScreen[3][2] * WorldPosition.z + WorldToScreen[3][3];

	if (Width < 0.001f)
		return false;

	const float Inverse = 1.0f / flWidth;
	ScreenPosition.x = (WorldToScreen[0][0] * WorldPosition.x + WorldToScreen[0][1] * WorldPosition.y + WorldToScreen[0][2] * WorldPosition.z + WorldToScreen[0][3]) * Inverse;
	ScreenPosition.y = (WorldToScreen[1][0] * WorldPosition.x + WorldToScreen[1][1] * WorldPosition.y + WorldToScreen[1][2] * WorldPosition.z + WorldToScreen[1][3]) * Inverse;

	const ImVec2 DisplaySize = ImGui::GetIO().DisplaySize;
	ScreenPosition.x = (DisplaySize.x * 0.5f) + (ScreenPosition.x * DisplaySize.x) * 0.5f;
	ScreenPosition.y = (DisplaySize.y * 0.5f) - (ScreenPosition.y * DisplaySize.y) * 0.5f;
	return true;
}

#pragma region UI_Elements

void UI::Header(const char* label) { // -------Group-------
    
};

bool UI::CheckBox(const char* label, bool value) {
    ImGuiWindow* window = GetCurrentWindow();
    if (window->SkipItems)
        return false;
 
    ImGuiContext &g = *GImGui;
    const ImGuiStyle &style = g.Style;
    const ImGuiID id = window->GetID(label);
    const ImVec2 label_size = CalcTextSize(label, NULL, true);
 
    const ImRect check_bb(window->DC.CursorPos, window->DC.CursorPos + ImVec2(label_size.y / 2 + style.FramePadding.y * 2, label_size.y / 2 + style.FramePadding.y * 2));
    ItemSize(check_bb, style.FramePadding.y);
 
    ImRect total_bb = check_bb;

    if (label_size.x > 0)
        SameLine(0, style.ItemInnerSpacing.x);

    const ImRect text_bb(window->DC.CursorPos + ImVec2(0, style.FramePadding.y), window->DC.CursorPos + ImVec2(0, style.FramePadding.y) + label_size);

    if (label_size.x > 0) {
        ItemSize(ImVec2(text_bb.GetWidth(), check_bb.GetHeight()), style.FramePadding.y);
        total_bb = ImRect(ImMin(check_bb.Min, text_bb.Min), ImMax(check_bb.Max, text_bb.Max));
    }
 
    if (!ItemAdd(total_bb, &id))
        return false;
 
    bool hovered, held;
    bool pressed = ButtonBehavior(total_bb, id, &hovered, &held);

    if (pressed)
        *value =! (*value);
 
    RenderFrame(check_bb.Min, check_bb.Max, GetColorU32((held && hovered)? ImGuiCol_FrameBgActive: hovered? ImGuiCol_FrameBgHovered: ImGuiCol_FrameBg), true, style.FrameRounding);
    
    if (*value) {
        const float check_sz = ImMin(check_bb.GetWidth (), check_bb.GetHeight ());
        const float pad = ImMax(1.0f, (float) (int) (check_sz / 6.0f));
        window->DrawList->AddRectFilled(check_bb.Min + ImVec2(pad, pad), check_bb.Max - ImVec2(pad, pad), GetColorU32(ImGuiCol_CheckMark), style.FrameRounding);
    }
 
    if (g.LogEnabled)
        LogRenderedText(text_bb.GetTL(), * value? "[X]": "[]");

    if (label_size.x > 0.0f)
        RenderText(text_bb.GetTL(), label);
 
    return pressed;
};

bool UI::ColorPicker(bool& bShowColorPicker, bool& bShowColorPickerAlt, ImVec4& color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f)) {
    if (ImGui::IsItemClicked(0)) {
        ImGui::Begin("##Colorpicker", bShowColorPicker, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse); {

        }
    }

    if (ImGui::IsItemClicked(1)) {
        ImGui::Begin("##Colorpickeralt", bShowColorPickerAlt, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse); {
            
        }

        //const char* ColorPickerOptions[] = {"Copy", "Paste"}
    }
};

int UI::Slider(const char* label, int value, int rangemin, int rangemax) {
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

int UI::DoubleSlider(const char* label, int valuemin, int valuemax, int rangemin, int rangemax) {

};

bool UI::DropDown(const char* label, const char* items) {


    if (ImGui::IsItemClicked(0)) {
        //render dropdown menu
    }
};

bool UI::DropdownMulti(const char* label, const char* items) {


    if (ImGui::IsItemClicked(0)) {
        //render dropdown menu
    }
};

bool TextBox(const char* label) {

};

void UI::KeyBind() { // [-]
    const char* KeyBindSelectedKeyDisplay[] = {};


    if (ImGui::IsItemClicked(1)) {
        const char* KeyBindOptions[] = {"Always", "Toggle", "On Hold", "Off Hold"};
    }
};


void UI::Console(std::string input) {

}

#pragma endregion