#include "../lib/log.hpp"

log::log(string _dir, bool _isKeepOpen, bool _printInConsole = false) {
   dir = _dir;
   isKeepOpen = _isKeepOpen;
   printInConsole = _printInConsole;

   if (!isdir()) {
      cout << "Eror log dir path invalid!" << endl;
      exit(1);
   }

   setMoment();
   day = moment->tm_mday;
   setPath();

   if (isKeepOpen) {
      if (!open()) {
         cout << "Error opening log file!" << endl;
         exit(2);
      }
   }

}

bool log::isdir() {
   struct stat sb;
   return stat(dir.c_str(), &sb) == 0;
}

bool log::open() {
   logfile = ofstream (path, ios_base::app);
   return logfile.is_open();
}


void log::loose() {
   logfile.close();
}

void log::setMoment() {
   time_t rawtime;
   time (&rawtime);
   moment = localtime (&rawtime);
}

void log::put(string logline) {
   if (printInConsole) {
      cout << logline << endl;
   }

   setMoment();
   setPrefix(logline);

   if (day != moment->tm_mday) {
      if (isKeepOpen && logfile.is_open()) {
         loose();
      }
      day = moment->tm_mday;
      setPath();
      if (isKeepOpen) {
         if (!open()) {
            cout << "Error opening log file!" << endl;
            exit(3);
         }
      }
   }

   if (!isKeepOpen || !logfile.is_open()) {      
      if (!open()) {
         cout << "Error opening log file!" << endl;
         exit(4);
      }
   }

   logfile << logline << endl;

   if (!isKeepOpen && logfile.is_open()) {
      loose();
   }

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

void log::setPrefix(string &logline) {
   stringstream hour, min, sec;
   hour << setw(2) << setfill('0') << moment->tm_hour;
   min << setw(2) << setfill('0') << moment->tm_min;
   sec << setw(2) << setfill('0') << moment->tm_sec;

   string _logline = hour.str() + ':' + min.str() + ':' + sec.str() + ' ' + logline;
   logline = _logline;
}

log::~log() {
   loose();
}

