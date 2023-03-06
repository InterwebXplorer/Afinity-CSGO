#include "filelogging.h"
#include "../../global.h"
#include <fstream>
#include <ctime>
#include <string>
#include <Windows.h>
#include <Shlobj.h>

void CreateLogFile() {
    Global::LogFileName = getlogfilename();
    std::string Path = getpathtologs() + Global::LogFileName;
    std::ofstream LogFile(Path);

    if (!LogFile.is_open())
        return;

    LogFile.close();
}

void WriteToLog(const std::string& Text) {
    std::string Path = getpathtologs() + Global::LogFileName;
    std::ofstream LogFile(Path, std::ios_base::app);

    if (!LogFile.is_open())
        return;

    if (LogFile.is_open())
        LogFile << "[" << getcurrenttime() << "]: " << Text << std::endl;
    else
        return;
        
    LogFile.close();
}

std::string getlogfilename() { //Result will look like this "03.10.22'14.26.45'CSGO.log"
    time_t Now = time(nullptr);
    tm* LocalTime = localtime(&Now);
    char FileName[32];
    strftime(FileName, sizeof(FileName), "%d.%m.%y''%H.%M.%S''CSGO.log", LocalTime);
    return FileName;
}

std::string getcurrenttime() {
    time_t Now = time(nullptr);
    tm* LocalTime = localtime(&Now);
    char Time[9];
    strftime(Time, sizeof(Time), "%H:%M:%S", LocalTime);
    return Time;
}

std::string getpathtologs() {
    char Path[MAX_PATH];

    if (SHGetSpecialFolderPathA(NULL, Path, CSIDL_APPDATA, FALSE))
        return Path + std::string("\\Roaming\\Afinity\\CSGO\\Logs\\");  
    return "";
}