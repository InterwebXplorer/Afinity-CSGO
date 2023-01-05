#pragma once
#include <string>

std::string getlogfilename();
std::string getcurrenttime();
std::string getpathtologs();
void createlogfile();
void writetolog(const std::string& text);