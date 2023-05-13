#include "../imgui/imgui.h"
#include "../imgui/imgui_freetype.h"
#include "../imgui/imgui_internal.h"
#include "../imgui/impl/imgui_impl_dx9.h"
#include "../imgui/impl/imgui_impl_win32.h"
#include "vector.h"
#include "draw.h"

#pragma region W2S
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
#pragma endregion

#pragma region UI_Elements
void UI::Header(const char* label) { // -------Group-------
    
};

bool UI::CheckBox(const char* Label, bool Value) {
    ImGuiWindow* Window = ImGui::GetCurrentWindow();

    if (Window->SkipItems)
        return false;

    ImGuiContext& G = *GImGui;
    const ImGuiStyle& Style = G.Style;
    const ImGuiID ID = Window->GetID(Label);

    const ImVec2 LabelSize = ImGui::CalcTextSize(Label, NULL, true);
    const ImRect CheckboxBoundingBox = ImRect(Window->DC.CursorPos, Window->DC.CursorPos + ImVec2(LabelSize.y / 2 + Style.FramePadding.y * 2, LabelSize.y / 2 + Style.FramePadding.y * 2));
    ImGui::ItemSize(CheckboxBoundingBox, Style.FramePadding.y);

    ImRect TotalBoundingBox = CheckboxBoundingBox;

    if (LabelSize.x > 0)
        ImGui::SameLine(0, Style.ItemInnerSpacing.x);

    const ImRect TextBoundingBox = ImRect(Window->DC.CursorPos + ImVec2(0, Style.FramePadding.y), Window->DC.CursorPos + ImVec2(0, Style.FramePadding.y) + LabelSize);

    if (LabelSize.x > 0) {
        ImGui::ItemSize(ImVec2(TextBoundingBox.GetWidth(), CheckboxBoundingBox.GetHeight()), Style.FramePadding.y);
        TotalBoundingBox = ImRect(ImMin(CheckboxBoundingBox.Min, TextBoundingBox.Min), ImMax(CheckboxBoundingBox.Max, TextBoundingBox.Max));
    }

    if (!ImGui::ItemAdd(TotalBoundingBox, &ID))
        return false;

    bool Hovered = false;
    bool Held = false;
    bool Pressed = ImGui::ButtonBehavior(TotalBoundingBox, ID, &Hovered, &Held);

    if (Pressed)
        *Value =! (*Value);

    ImGui::RenderFrame(CheckboxBoundingBox.Min, CheckboxBoundingBox.Max, ImGui::GetColorU32((Held && Hovered)? ImGuiCol_FrameBgActive: Hovered? ImGuiCol_FrameBgHovered: ImGuiCol_FrameBg), true, Style.FrameRounding);

    if (*Value) {
        const float CheckboxSize = ImMin(CheckboxBoundingBox.GetWidth(), CheckboxBoundingBox.GetHeight());
        const float Padding = ImMax(1.0f, (float) (int) (CheckboxSize / 6.0f));
        Window->DrawList->AddRectFilled(CheckboxBoundingBox.Min + ImVec2(Padding, Padding), CheckboxBoundingBox.Max - ImVec2(Padding, Padding), ImGui::GetColorU32(ImGuiCol_CheckMark), Style.FrameRounding);
    }

    if (G.LogEnabled)
        ImGui::LogRenderedText(TextBoundingBox.GetTL(), * Value? "[X]":"[]");

    if (LabelSize.x > 0.0f)
        ImGui::RenderText(TextBoundingBox.GetTL(), Label);

    return Pressed;
};

void UI::ColorPicker(const char* Label, ImVec4 Color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f)) {
    ImGuiWindow* Window = ImGui::GetCurrentWindow();

    if (Window->SkipItems)
        return;

    ImGuiContext& G = *GImGui;
    const ImGuiStyle& Style = G.Style;
    const ImGuiID ID = Window->GetID(Label);

    //
    static bool ShowColorPicker = false;
    static bool ShowColorPickerAlt = false;


    if (ImGui::IsItemClicked(0)) {
        ImGui::Begin("##Colorpicker", ShowColorPicker, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse); {

        }
    }

    if (ImGui::IsItemClicked(1)) {
        ImGui::Begin("##Colorpickeralt", ShowColorPickerAlt, ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse); {
            
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