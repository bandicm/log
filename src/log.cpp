#include "../lib/log.hpp"

marcelb::log::log(string _dir, Level _loglevel, bool _isKeepOpen, bool _printInConsole) {
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

bool marcelb::log::isdir() {
   struct stat sb;
   return stat(dir.c_str(), &sb) == 0;
}

bool marcelb::log::open() {
   logfile = ofstream (path, ios_base::app);
   return logfile.is_open();
}


void marcelb::log::loose() {
   logfile.close();
}

void marcelb::log::setMoment() {
   time_t rawtime;
   time (&rawtime);
   moment = localtime (&rawtime);
}

void marcelb::log::put(string logline, Level _level) {
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
      if (isKeepOpen && logfile.is_open()) {
         loose();
      }
      day = moment->tm_mday;
      setPath();
      if (isKeepOpen) {
         if (!open()) {
            throw string("[ERROR] Opening log file! ");
         }
      }
   }

   if (!isKeepOpen || !logfile.is_open()) {      
      if (!open()) {
         throw string("[ERROR] Opening log file! ");
      }
   }

   logfile << logline << endl;

   if (!isKeepOpen && logfile.is_open()) {
      loose();
   }
   io.unlock();

}

void marcelb::log::setPath() {
   if (dir[dir.length()-1] != '/') {
      dir.push_back('/');
   }
   
   stringstream mon, _day;
   mon << setw(2) << setfill('0') << moment->tm_mon+1;
   _day << setw(2) << setfill('0') << moment->tm_mday;
   path = dir + to_string(moment->tm_year+1900) + '-' + mon.str() + '-' + _day.str() + ".log";
}

void marcelb::log::setPrefix(string &logline, Level &_level) {
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

void marcelb::log::debug(string logline) {
   put(logline, DEBUG);
}

void marcelb::log::info(string logline) {
   put(logline, INFO);
}

void marcelb::log::warning(string logline) {
   put(logline, WARNING);
}

void marcelb::log::error(string logline) {
   put(logline, ERROR);
}

void marcelb::log::fatal(string logline) {
   put(logline, FATAL);
}


marcelb::log::~log() {
   loose();
}

