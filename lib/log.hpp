#ifndef _LOG_
#define _LOG_

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include <time.h>
#include <sys/stat.h>
#include <mutex>

#if _WIN32
typedef unsigned int uint;
#endif
namespace marcelb {
namespace logging {

using namespace std;

/**
 * Log class - used at the level of one log directory
*/
class log {
    string dir;
    bool isKeepOpen;
    bool printInConsole;
    ofstream logfile;
    struct tm * moment;
    uint day;
    string path;
    mutex io;

    /**
     * Checking if the path is in the string dir directory
    */
    bool isdir();

    /**
     * Opens the log file
    */
    bool open();

    /**
     * Closes the log file
    */
    void loose();

    /**
     * Get time
    */
    void setMoment();

    /**
     * Generate full log file path
    */
    void setPath();

    /**
     * Set log line time prefix
    */
    void setPrefix(string &logline);

    public:

    /**
     * Constructor,
     * receives the log directory path,
     * optional: a bool variable if it keeps the file open, 
     * and a bool variable if it prints log lines to the console
    */
    log (string _dir, bool _isKeepOpen = true, bool _printInConsole = false);

    /**
     * Put string log in file
    */
    void put(string logline);

    /**
     * Destruktor, close log files
    */
    ~log();
};

}
}

#endif