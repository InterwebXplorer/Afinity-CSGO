// imgui_stdlib.h
// Wrappers for C++ standard library (STL) types (std::string, etc.)
// This is also an example of how you may wrap your own similar types.

// Compatibility:
// - std::string support is only guaranteed to work from C++11.
//   If you try to use it pre-C++11, please share your findings (w/ info about compiler/architecture)

// Changelog:
// - v0.10: Initial version. Added InputText() / InputTextMultiline() calls with std::string

#pragma once
#include "imgui/imgui.h"
#define IMGUI_DEFINE_MATH_OPERATORS
#include "imgui/imgui_internal.h"
#include <Windows.h>
#include <string>
#include <functional>
#include <vector>

namespace ImGui
{
    // ImGui::InputText() with std::string
    // Because text input needs dynamic resizing, we need to setup a callback to grow the capacity
    IMGUI_API bool  InputText(const char* label, std::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
    IMGUI_API bool  InputTextMultiline(const char* label, std::string* str, const ImVec2& size = ImVec2(0, 0), ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
    IMGUI_API bool  InputTextWithHint(const char* label, const char* hint, std::string* str, ImGuiInputTextFlags flags = 0, ImGuiInputTextCallback callback = NULL, void* user_data = NULL);
	bool ToggleButton(const char* label, bool* v, const ImVec2& size_arg = ImVec2(0, 0));
	// Combo box helper allowing to pass an array of strings.
	bool Combo(const char* label, int* currIndex, std::vector<std::string>& values);
	bool BeginGroupBox(const char* name, const ImVec2& size_arg = ImVec2(0, 0));
	void EndGroupBox();
	bool Hotkey(const char* label, int* k, const ImVec2& size_arg = ImVec2(0, 0));
	bool ListBox(const char* label, int* current_item, std::string items[], int items_count, int height_items);
	bool ListBox(const char* label, int* current_item, std::function<const char* (int)> lambda, int items_count, int height_in_items);
	bool Combo(const char* label, int* current_item, std::function<const char* (int)> lambda, int items_count, int height_in_items);
}
