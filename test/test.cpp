#include <iostream>

#include "../lib/log.hpp"

using namespace std;

int main() {

    log mylog("../example", false);

    mylog.put("[EVENT] Start loging");

    return 0;
}