
# A simple Logging library for C++ programs

Logging errors to a file, daily file rotation, date and time stamps. Configurable record structure etc. 


## Features

- Object oriented
- Customizable directory for files
- Daily file rotation
- Protection of recording consecutive errors
- Log levels
- Thread safe
- Exceptions
- The possibility of printing logs in the console
- Ability to keep log file open for faster speed
- Supports multiple simultaneous log files by custom directories

## Installation

Just download the latest release and unzip it into your project. You can turn it on with:

```
#include "log/lib/log.hpp"
using namespace marcelb;
```

## Usage

```c++
/**
* Initialization and declaration
*/
log mylog("../log", Level::INFO);

/**
* Put log in file
*/
mylog.debug("Debug loging");
mylog.info("Info loging");
mylog.warning("Warning loging");
mylog.error("Error loging");
mylog.fatal("Fatal loging");
```
## License

[APACHE 2.0](http://www.apache.org/licenses/LICENSE-2.0/)


## Support & Feedback

For support and any feedback, contact the address: marcelb96@yahoo.com.

## Contributing

Contributions are always welcome!

Feel free to fork and start working with or without a later pull request. Or contact for suggest and request an option.

