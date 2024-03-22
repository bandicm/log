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

using namespace std;

typedef enum {
    DEBUG = 0,
    INFO,
    WARNING,
    ERROR,
    FATAL,
} Level;

/**
 * Log class - used at the level of one log directory
*/
class log {
    string dir;
    Level loglevel;
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
    void setPrefix(string &logline, Level &_level);

    /**
     * Put string log in file
    */
    void put(string logline, Level _level);

    public:

    /**
     * Constructor,
     * receives the log directory path,
     * optional: a bool variable if it keeps the file open, 
     * and a bool variable if it prints log lines to the console
    */
    log (string _dir, Level loglevel = WARNING, bool _isKeepOpen = true, bool _printInConsole = false);


    /**
     * Debug log line
    */
    void debug(string logline);

    /**
     * Info log line
    */
    void info(string logline);

    /**
     * Warning log line
    */
    void warning(string logline);

    /**
     * Error log line
    */
    void error(string logline);

    /**
     * Fatal log line
    */
    void fatal(string logline);

    /**
     * Destruktor, close log files
    */
    ~log();
};

}

#endif