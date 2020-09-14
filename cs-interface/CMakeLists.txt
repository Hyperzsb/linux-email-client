cmake_minimum_required(VERSION 3.17)
project(client_new)

set(CMAKE_CXX_STANDARD 11)

include_directories(/home/guangtao/桌面/client_new/info-acc)
include_directories(/home/guangtao/桌面/client_new/cJSON_PACKAGES)
include_directories(/usr/local/include/cjson)
link_directories(//usr/local/lib)
link_libraries(cjson)

find_package(PkgConfig REQUIRED)
pkg_check_modules(GTK3 REQUIRED gtk+-3.0)

include_directories(${GTK3_INCLUDE_DIRS})
link_directories(${GTK3_LIBRARY_DIRS})

add_definitions(${GTK3_CFLAGS_OTHER})

add_executable(client_new main.c cJSON_PACKAGES.c cJSON_PACKAGES.h
        info-acc.h info-acc.c PRE_CONDITIONS.h
        SetContact/SetContact.c SetContact/SetContact.h GetContact/GetContact.c GetContact/GetContact.h SaveDraft/SaveDraft.c SaveDraft/SaveDraft.h)

find_package(Threads REQUIRED)
target_link_libraries(client_new Threads::Threads)
target_link_libraries(client_new cjson)
target_link_libraries(client_new m)
target_link_libraries(client_new ${GTK3_LIBRARIES})