#include "filelogging.h"
#include <fstream>
#include <xstring>


std::string getdatetime(string datetime) {
    
}

std::string getcurrenttime(string time) {
    
}

std::string getfilepath(string path) {

}

void createlogfile() {

}

void writetolog(string text) { //e.g. 03.10.22''14.26.45''CSGO.log
    string logpath = getfilepath("path")+getdatetime("datetime")+"CSGO.log";
    string currenttime = getcurrenttime("time");
}