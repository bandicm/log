#include <iostream>

#include "../lib/log.hpp"

using namespace std;
using namespace marcelb::logging;

log mylog("../example", Level::INFO, false);
// log mylog("../example", [](string log, string path) {
//     cout << log << " " << path << endl;
// }, Level::INFO);

int main() {
    mylog.debug("Start debug loging");
    mylog.info("Start info loging");
    mylog.warning("Start warning loging");
    mylog.error("Start error loging");
    mylog.fatal("Start fatal loging");

    return 0;
}
