#include "../lib/log.hpp"

namespace marcelb {
namespace logging {

log::log(string _dir, Level _loglevel, bool _isKeepOpen, bool _printInConsole) {
   dir = _dir;
   loglevel = _loglevel;
   isKeepOpen = _isKeepOpen;
   printInConsole = _printInConsole;

   if (!isdir()) {
      throw string("[ERROR] Log dir path invalid ");
   }

   setMoment();
   day = moment->tm_mday;
   setPath();

   if (isKeepOpen) {
      if (!open()) {
         throw string("[ERROR] Opening log file! ");
      }
   }

}

log::log (string _dir, function<void(string, string)> _extWriter, Level _loglevel, bool _printInConsole) {
   dir = _dir;
   loglevel = _loglevel;
   extWriter = _extWriter;
   printInConsole = _printInConsole;
   setMoment();
   day = moment->tm_mday;
   setPath();
}


bool log::isdir() {
   struct stat sb;
   return stat(dir.c_str(), &sb) == 0;
}

bool log::open() {
   if (extWriter) {
      return false;
   }
   logfile = ofstream (path, ios_base::app);
   return logfile.is_open();
}


void log::loose() {
   if (!extWriter) {
      logfile.close();
   }
}

void log::setMoment() {
   time_t rawtime;
   time (&rawtime);
   moment = localtime (&rawtime);
}

void log::put(string logline, Level _level) {
   if (_level < loglevel)  {
      return;
   }
   io.lock();
   if (printInConsole) {
      cout << logline << endl;
   }

   setMoment();
   setPrefix(logline, _level);

   if (day != moment->tm_mday) {
      if (!extWriter && isKeepOpen && logfile.is_open()) {
         loose();
      }
      day = moment->tm_mday;
      setPath();
      if (!extWriter && isKeepOpen) {
         if (!open()) {
            throw string("[ERROR] Opening log file! ");
         }
      }
   }

   if (!extWriter && (!isKeepOpen || !logfile.is_open())) {      
      if (!open()) {
         throw string("[ERROR] Opening log file! ");
      }
   }

   if (!extWriter) {
      logfile << logline << endl;
   } else {
      extWriter(logline, path);
   }

   if (!extWriter && !isKeepOpen && logfile.is_open()) {
      loose();
   }
   io.unlock();

}

void log::setPath() {
   if (dir[dir.length()-1] != '/') {
      dir.push_back('/');
   }
   
   stringstream mon, _day;
   mon << setw(2) << setfill('0') << moment->tm_mon+1;
   _day << setw(2) << setfill('0') << moment->tm_mday;
   path = dir + to_string(moment->tm_year+1900) + '-' + mon.str() + '-' + _day.str() + ".log";
}

void log::setPrefix(string &logline, Level &_level) {
   stringstream hour, min, sec;
   hour << setw(2) << setfill('0') << moment->tm_hour;
   min << setw(2) << setfill('0') << moment->tm_min;
   sec << setw(2) << setfill('0') << moment->tm_sec;

   string _logline = hour.str() + ':' + min.str() + ':' + sec.str();// + logline;
   switch (_level) {
      case DEBUG:
         _logline += " [DEBUG]   ";
         break;
      case INFO:
         _logline += " [INFO]    ";
         break;
      case WARNING:
         _logline += " [WARNING] ";
         break;
      case ERROR:
         _logline += " [ERROR]   ";
         break;
      case FATAL:
         _logline += " [FATAL]   ";
         break;
      default:
         _logline += " [UNAKOWN] ";
         break;

   }
   logline = _logline + logline;
}

void log::debug(string logline) {
   put(logline, DEBUG);
}

void log::info(string logline) {
   put(logline, INFO);
}

void log::warning(string logline) {
   put(logline, WARNING);
}

void log::error(string logline) {
   put(logline, ERROR);
}

void log::fatal(string logline) {
   put(logline, FATAL);
}


log::~log() {
   loose();
}


}
}
