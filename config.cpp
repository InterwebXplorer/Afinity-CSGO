#include <shlobj.h>
#include <filesystem>
#include "resources/utils/filelogging.h"
#include "config.h"

/*
UI::Textbox("Name", Options.config_name);
ImGui::Button("Create", ImVec2(276, 30), Options.config_create);
ImGui::Button("Save", ImVec2(276, 30), Options.config_save);
ImGui::Button("Load", ImVec2(276, 30), Options.config_load);
ImGui::Button("Delete", ImVec2(276, 30), Options.config_delete);
ImGui::Button("Reset", ImVec2(276, 30), Options.config_reset);
*/

void config::setup() {
    if (!getpath()) {
        writetolog("[Error] Failed to get config path \n Creating path...");

        if (!filesystem::create_directories("/Afinity/CSGO/config/")) {
            writetolog("[Error] Failed to create path");
            return;
        }
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

bool config::create(std::string name) {

}

bool config::save(std::string name) {

}

bool config::load(std::string name) {

}

bool config::remove(std::string name) {

}

bool config::reset(std::string name) {
    
}

void config::refresh() {

}

filesystem::path config::getpath() {
    TCHAR szPath[MAX_PATH];
    SHGetFolderPath(nullptr, CSIDL_APPDATA, nullptr, 0, szPath);

    const char* fsPath = filesystem::path(szPath);
    fsPath.append("/Afinity/CSGO/config/");

    return fsPath;
}