#pragma once
#include <d3d9.h>

namespace menu { //text = 20pt arial
    constexpr int borderwidth = 900;
    constexpr int borderheight = 500;
    constexpr int menuwidth = 880;
    constexpr int menuheight = 480;
    constexpr int contentwidth = 716;
    constexpr int contentheight = 432;
    constexpr int sidebarwidth = 137;
    constexpr int sidebarheight = 432;
    constexpr int sidebarbuttonheight = 62;
    constexpr int maximumtopbarwidth = 716; //math to devide this for buttons //topbarwidth = maximumtopbarwidth / numberoftabs //Just manually set this stuff :(
    constexpr int topbarheight = 26;

    style.Colors[ImGuiCol_Border] = ImVec4(27,38,44,255);
    style.Colors[ImGuiCol_Background] = ImVec4(37,45,56,255);
    //Logo?
    style.Colors[ImGuiCol_SidebarPanel] = ImVec4(51,64,74,255);
    style.Colors[ImGuiCol_SidebarTabBase] = ImVec4(51,64,74,255);
    style.Colors[ImGuiCol_SidebarTabTextBase] = ImVec4(255,255,255,255);
    style.Colors[ImGuiCol_SidebarTabSelected] = ImVec4();
    style.Colors[ImGuiCol_SidebarTabTextSelected] = ImVec4(255,255,255,255);
    //steam profile picture
    style.Colors[ImGuiCol_UserText] = ImVec4(255,255,255,255); //steam profile steamname/steamid/configname
    style.Colors[ImGuiCol_TopbarPanel] = ImVec4(51,64,74,255);
    style.Colors[ImGuiCol_TopbarTabBase] = ImVec4(51,64,74,255);
    style.Colors[ImGuiCol_TopbarTabTextBase] = ImVec4(255,255,255,255);
    style.Colors[ImGuiCol_TopbarTabSelected] = ImVec4();
    style.Colors[ImGuiCol_TopbarTabTextSelected] = ImVec4(255,255,255,255);
    style.Colors[ImGuiCol_MainPanel] = ImVec4(51,64,74,255);
    style.Colors[ImGuiCol_GroupLine] = ImVec4(255,255,255,255);
    style.Colors[ImGuiCol_GroupText] = ImVec4(255,255,255,255);
    style.Colors[ImGuiCol_CheckboxBase] = ImVec4();
    style.Colors[ImGuiCol_CheckboxOutline] = ImVec4();
    style.Colors[ImGuiCol_CheckboxText] = ImVec4(255,255,255,255);
    style.Colors[ImGuiCol_CheckboxSelected] = ImVec4();
    style.Colors[ImGuiCol_SliderBase] = ImVec4();
    style.Colors[ImGuiCol_SliderText] = ImVec4(255,255,255,255)
    style.Colors[ImGuiCol_SliderSelected] = ImVec4();;
    style.Colors[ImGuiCol_DoubleSilderBase] = ImVec4();
    style.Colors[ImGuiCol_DoubleSliderText] = ImVec4(255,255,255,255);
    style.Colors[ImGuiCol_DoubleSliderSlected] = ImVec4();
    style.Colors[ImGuiCol_DropdownBase] = ImVec4();
    style.Colors[ImGuiCol_DropdownOutline] = ImVec4();
    style.Colors[ImGuiCol_DropdownText] = ImVec4(255,255,255,255);
    style.Colors[ImGuiCol_DropdownSelected] = ImVec4();
    style.Colors[ImGuiCol_DropdownTextSelected] = ImVec4(255,255,255,255);
    style.Colors[ImGuiCol_DropdownMultiBase] = ImVec4();
    style.Colors[ImGuiCol_DropdownMultiOutline] = ImVec4();
    style.Colors[ImGuiCol_DropdownMultiText] = ImVec4(255,255,255,255);
    style.Colors[ImGuiCol_DropdownMultiSelected] = ImVec4();
    style.Colors[ImGuiCol_DropdownMultiTextSelected] = ImVec4(255,255,255,255);
    style.Colors[ImGuiCol_TextBoxBase] = ImVec4();
    style.Colors[ImGuiCol_TextBoxText] = ImVec4(255,255,255,255);
    style.Colors[ImGuiCol_TextBoxSelected] = ImVec4();
    style.Colors[ImGuiCol_ListBoxBase] = ImVec4();
    style.Colors[ImGuiCol_ListBoxText] = ImVec4(255,255,255,255);
    style.Colors[ImGuiCol_ListBoxSelected] = ImVec4();
    style.Colors[ImGuiCol_ListBoxTextSelected] = ImVec4(255,255,255,255);
    style.Colors[ImGuiCol_KeyBindBase] = ImVec4(255,255,255,255);
    style.Colors[ImGuiCol_KeyBindSelected] = ImVec4();
    style.Colors[ImGuiCol_ScrollBarBase] = ImVec4();
    style.Colors[ImGuiCol_ScrollBarSelected] = ImVec4();

    //void MainWindow(IDirect3DDevice9* pDevice);

    inline bool Show = true;

    //imgui flags?

    void RenderLegitTab();
    void RenderRageTab();
    void RenderEspTab();
    void RenderAntiAimTab();
    void RenderModifierTab();
    void RenderMiscTab();

    inline int currentsidebartab = 0;
    inline int currenttopbartab = 0;
    //config names/text inputs here
}