cmake_minimum_required(VERSION 3.17)
project(cs-interface)

set(CMAKE_CXX_STANDARD 11)

include_directories(/home/guangtao/桌面/cs-interface/info-acc)
include_directories(/home/guangtao/桌面/cs-interface/cJSON_PACKAGES)
include_directories(/usr/local/include/cjson)
link_directories(//usr/local/lib)
link_libraries(cjson)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(cs-interface main.c DEMO.c define.h)
find_package(Threads REQUIRED)
target_link_libraries(cs-interface Threads::Threads)
target_link_libraries(cs-interface cjson)
target_link_libraries(cs-interface m)
target_link_libraries(cs-interface ${GTK3_LIBRARIES})