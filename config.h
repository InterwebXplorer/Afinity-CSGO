#pragma once
#include <string>

namespace Config {
    void Setup();
    bool Create(std::string& name = "default.afinity");
    bool Save(std::string& name);
    bool Load(std::string& name);
    bool Remove(std::string& name);
    bool Reset(std::string& name);
    void Refresh();
    void getconfigfiles();
    std::string getpathtoconfigs();
}