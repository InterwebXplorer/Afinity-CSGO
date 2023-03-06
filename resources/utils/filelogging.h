#pragma once
#include <string>

void CreateLogFile();
void WriteToLog(const std::string& Text);
std::string getlogfilename();
std::string getcurrenttime();
std::string getpathtologs();