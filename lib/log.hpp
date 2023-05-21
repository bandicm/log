#ifndef _LOG_
#define _LOG_

#include <iostream>
#include <iomanip>
#include <string>
#include <fstream>
#include <time.h>
#include <sys/stat.h>

using namespace std;

class log {
    public:
    string dir;
    bool isKeepOpen;
    ofstream logfile;
    struct tm * moment;
    uint day;
    string path;

    log (string _dir, bool _isKeepOpen = true);

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