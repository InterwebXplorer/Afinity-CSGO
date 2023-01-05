#include "../imgui/imgui.h"
#include "../imgui/imgui_freetype.h"
#include "../imgui/imgui_internal.h"
#include "../imgui/impl/imgui_impl_dx9.h"
#include "../imgui/impl/imgui_impl_win32.h"
#include "vector.h"
#include "draw.h"

bool draw::w2s(const Vector3& worldposition, ImVec2& screenposition) {
    const ViewMatrix_t& matWorldToScreen = I::Engine->WorldToScreenMatrix();
	const float flWidth = matWorldToScreen[3][0] * vecOrigin.x + matWorldToScreen[3][1] * vecOrigin.y + matWorldToScreen[3][2] * vecOrigin.z + matWorldToScreen[3][3];

	if (flWidth < 0.001f)
		return false;

	const float flInverse = 1.0f / flWidth;
	vecScreen.x = (matWorldToScreen[0][0] * vecOrigin.x + matWorldToScreen[0][1] * vecOrigin.y + matWorldToScreen[0][2] * vecOrigin.z + matWorldToScreen[0][3]) * flInverse;
	vecScreen.y = (matWorldToScreen[1][0] * vecOrigin.x + matWorldToScreen[1][1] * vecOrigin.y + matWorldToScreen[1][2] * vecOrigin.z + matWorldToScreen[1][3]) * flInverse;

	const ImVec2 vecDisplaySize = ImGui::GetIO().DisplaySize;
	vecScreen.x = (vecDisplaySize.x * 0.5f) + (vecScreen.x * vecDisplaySize.x) * 0.5f;
	vecScreen.y = (vecDisplaySize.y * 0.5f) - (vecScreen.y * vecDisplaySize.y) * 0.5f;
	return true;
}

#pragma region ui_elements
void Header(const char* label) { // -------Group-------
    
};

bool CheckBox(const char* label, bool value) {

};

bool ColorPicker(bool& bShowColorPicker, bool& bShowColorPickerAlt, ImVec4& color = ImVec4(0.0f, 0.0f, 0.0f, 0.0f)) {
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
#pragma endregion