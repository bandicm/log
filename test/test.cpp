#include <iostream>
#include <unistd.h>

#include "../lib/log.hpp"

using namespace std;
using namespace marcelb::logging;

log mylog("../example", Level::DEBUG, true, false, 5);

int main() {
    // mylog.debug("Start debug loging");
    // mylog.info("Start info loging");
    // mylog.warning("Start warning loging");
    // mylog.error("Start error loging");
    // mylog.fatal("Start fatal loging");

    int i = 0;
    while(true) {
        mylog.fatal("Test fatal error: "+ to_string(i++));
        sleep(2);
    }

    return 0;
}
