#ifndef _LOG_
#define _LOG_

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <time.h>
#include <sys/stat.h>
#include <mutex>

using namespace std;

class log {
    public:
    string dir;
    bool isKeepOpen;
    bool printInConsole;
    ofstream logfile;
    struct tm * moment;
    uint day;
    string path;
    mutex io;

    log (string _dir, bool _isKeepOpen = true, bool _printInConsole = false);

    bool isdir();
    bool open();
    void loose();
    void setMoment();
    void setPath();
    void put(string logline);
    void setPrefix(string &logline);

    ~log();
};


#endif