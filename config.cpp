#include "resources/utils/filelogging.h"
#include "config.h"
#include "options.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <Windows.h>
#include <Shlobj.h>

void config::setup() {
    if (!getpathtoconfigs) {
        writetolog("[Error] Failed to get config path")
        return;
    }

    if (!create(default.afinity)) {
        writetolog("[Error] Failed to create default config")
        return;
    }

    if (!save(default.afinity)) {
        writetolog("[Error] Failed to save default config");
        return;
    }

    if (!load(default.afinity)) {
        writetolog("[Error] Failed to load default config");
        return;
    }

    if (!refresh()) {
        writetolog("[Error] Failed to refresh configs");
        return;
    }

    writetolog("[Success] Config setup complete");
}

bool config::create(std::string& name = "default.afinity") {
    if (!Options.config_create)
        return;

    if (name.find(".afinity") == std::string::npos)
        name += ".afinity";

    std::string path = getpathtoconfigs() + name;

    if (std::filesystem::exists(path))
        return false;

    std::ofstream config_file(path);

    if (!config_file.is_open())
        return false;

    for (size_t i = 0; i < DefaultOptions.size(); i++) {
        config_file << DefaultOptions[i] << std::endl;
    }

    config_file.close();
    return true;
}

bool config::save(std::string& name) {
    if (!Options.config_save)
        return;

    std::string path = getpathtoconfigs() + name;
    std::ofstream config_file(path, std::ios::out | std::ios::trunc);

    if (!config_file.is_open())
        return false;

    for (size_t i = 0; i < Options.size(); i++) {
        config_file << Options[i] << std::endl;
    }

    config_file.close();
    return true;
}

bool config::load(std::string& name) {
    if (!Options.config_load)
        return;

    std::string path = getpathtoconfigs() + name;
    std::ifstream config_file(path);

    if (!config_file.is_open())
        return false;

    for (size_t i = 0; i < Options.size(); i++) {
        config_file >> Options[i];
    }

    config_file.close();
    return true;
}

bool config::remove(std::string& name) {
    if (!Options.config_delete)
        return;

    std::string path = getpathtoconfigs() + name;
    return std::remove(path);
}

bool config::reset(std::string& name) {
    if (!Options.config_reset)
        return;

    return load(default.afinity)
}

void config::refresh() {
    if (!Options.config_refresh)
        return;

    return getconfigfiles();
}

void config::getconfigfiles() {
    std::string path = getpathtoconfigs();
    std::vector<std::string> configlist;

    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file() && entry.path().extension() = ".afinity") {
            configlist.push_back(entry.path().filename().string());
        }
    }
}

std::string config::getpathtoconfigs() {
    char path[MAX_PATH];

    if (SHGetSpecialFolderPathA(NULL, path, CSIDL_APPDATA, FALSE))
        return path + std::string("\\Roaming\\Afinity\\CSGO\\Configs\\");  
    return "";
}

/*
UI::Textbox("Name", Options.config_name);
ImGui::Button("Create", ImVec2(276, 30), Options.config_create);
ImGui::Button("Save", ImVec2(276, 30), Options.config_save);
ImGui::Button("Load", ImVec2(276, 30), Options.config_load);
ImGui::Button("Delete", ImVec2(276, 30), Options.config_delete);
ImGui::Button("Reset", ImVec2(276, 30), Options.config_reset);
*/