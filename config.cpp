#include "resources/utils/filelogging.h"
#include "config.h"
#include "options.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <string>
#include <Windows.h>
#include <Shlobj.h>

void Config::Setup() {
    if (!getpathtoconfigs) {
        WriteToLog("[Error] Failed to get config path")
        return;
    }

    if (!Create("default.afinity")) {
        WriteToLog("[Error] Failed to create default config")
        return;
    }

    if (!Save("default.afinity")) {
        WriteToLog("[Error] Failed to save default config");
        return;
    }

    if (!load("default.afinity")) {
        WriteToLog("[Error] Failed to load default config");
        return;
    }

    if (!refresh()) {
        WriteToLog("[Error] Failed to refresh configs");
        return;
    }

    WriteToLog("[Success] Config setup complete");
}

bool Config::Create(std::string& name = "default.afinity") {
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

bool Config::Save(std::string& name) {
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

bool Config::Load(std::string& name) {
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

bool Config::Remove(std::string& name) {
    if (!Options.config_delete)
        return;

    std::string path = getpathtoconfigs() + name;
    return std::remove(path);
}

bool Config::Reset(std::string& name) {
    if (!Options.config_reset)
        return;

    return Load("default.afinity");
}

void Config::Refresh() {
    if (!Options.config_refresh)
        return;

    return getconfigfiles();
}

void Config::getconfigfiles() {
    std::string path = getpathtoconfigs();
    std::vector<std::string> configlist;

    for (const std::filesystem::directory_entry& entry : std::filesystem::directory_iterator(path)) {
        if (entry.is_regular_file() && entry.path().extension() = ".afinity") {
            configlist.push_back(entry.path().filename().string());
        }
    }
}

std::string Config::getpathtoconfigs() {
    char path[MAX_PATH];

    if (SHGetSpecialFolderPathA(NULL, path, CSIDL_APPDATA, FALSE))
        return path + std::string("\\Roaming\\Afinity\\CSGO\\Configs\\");  
    return "";
}