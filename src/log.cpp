#include "../lib/log.hpp"

marcelb::log::log(string _dir, bool _isKeepOpen, bool _printInConsole) {
   dir = _dir;
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

void marcelb::log::put(string logline) {
   io.lock();
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

void marcelb::log::setPrefix(string &logline) {
   stringstream hour, min, sec;
   hour << setw(2) << setfill('0') << moment->tm_hour;
   min << setw(2) << setfill('0') << moment->tm_min;
   sec << setw(2) << setfill('0') << moment->tm_sec;

   string _logline = hour.str() + ':' + min.str() + ':' + sec.str() + ' ' + logline;
   logline = _logline;
}

marcelb::log::~log() {
   loose();
}

