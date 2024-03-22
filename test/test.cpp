#include <iostream>

#include "../lib/log.hpp"

using namespace std;
using namespace marcelb;

log mylog("../example", Level::FATAL, false);

int main() {
    mylog.debug("Start debug loging");
    mylog.info("Start info loging");
    mylog.warning("Start warning loging");
    mylog.error("Start error loging");
    mylog.fatal("Start fatal loging");

    return 0;
}
