#include "filelogging.h"
#include "../../global.h"
#include <fstream>
#include <ctime>
#include <string>
#include <Windows.h>
#include <Shlobj.h>

std::string getlogfilename() { //Result will look like this "03.10.22'14.26.45'CSGO.log"
    time_t now = time(nullptr);
    tm* localtime = localtime(&now);
    char filename[32];
    strftime(filename, sizeof(filename), "%d.%m.%y''%H.%M.%S''CSGO.log", localtime);
    return filename;
}

std::string getcurrenttime() {
    time_t now = time(nullptr);
    tm* localtime = localtime(&now);
    char time[9];
    std::strftime(time, sizeof(time), "%H:%M:%S", localtime);
    return time;
}

std::string getpathtologs() {
    char path[MAX_PATH];

    if (SHGetSpecialFolderPathA(NULL, path, CSIDL_APPDATA, FALSE))
        return path + std::string("\\Roaming\\Afinity\\CSGO\\Logs\\");  
    return "";
}

void createlogfile() {
    Global::logfilename = getlogfilename();
    std::string path = getpathtologs() + Global::logfilename;
    std::ofstream log_file(path);

    if (!log_file.is_open())
        return;

    log_file.close();
}

void writetolog(const std::string& text) {
    std::string path = getpathtologs() + Global::logfilename;
    std::ofstream log_file(path, std::ios_base::app);

    if (!log_file.is_open())
        return;

    if (log_file.is_open())
        log_file << "[" << getcurrenttime() << "]: " << text << std::endl;
    else
        return;
        
    log_file.close();
}