#include <iostream>

#include "../lib/log.hpp"

using namespace std;
using namespace marcelb::logging;

log mylog("../example", false);

int main() {

//     log mylog("../example", false);

    mylog.put("[EVENT] Start loging");

    return 0;
}
