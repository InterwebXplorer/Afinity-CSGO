#pragma once
#include <string>

namespace config {
    void setup();
    bool create(std::string& name = "default.afinity");
    bool save(std::string& name);
    bool load(std::string& name);
    bool remove(std::string& name);
    bool reset(std::string& name);
    void refresh();
    void getconfigfiles();
    std::string getpathtoconfigs();
}