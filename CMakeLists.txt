cmake_minimum_required(VERSION 3.10)

project(log)

# Postavi verziju projekta
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Pronađi Boost biblioteku (ako nije uobičajeni direktorijum, postavi put)
# find_package(Boost REQUIRED COMPONENTS system)

# Dodaj direktorijume sa zaglavljima
include_directories(lib)

# Dodaj biblioteku
add_library(log STATIC
    src/log.cpp
)

# # Linkaj log biblioteku sa Boost-om
# target_link_libraries(log Boost::system)

# Dodaj testove
add_subdirectory(test)


# Instaliraj biblioteku
# install(TARGETS log DESTINATION lib)
# install(FILES lib/log.hpp lib/define.hpp lib/engine.hpp lib/filesystem.hpp lib/timers.hpp lib/trigger.hpp DESTINATION include/log)
# 