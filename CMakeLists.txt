cmake_minimum_required(VERSION 3.7)
project(gemian-lock)
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)

set(CMAKE_CXX_STANDARD 14)

set(GEMIAN_LOCK_VERSION "2.10")

find_package(ECM REQUIRED NO_MODULE)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH};${ECM_MODULE_PATH};${ECM_KDE_MODULE_DIR}")

include(GNUInstallDirs)

find_package(PkgConfig)

find_package(PAM REQUIRED)
find_package(EV REQUIRED)
find_package(XCB REQUIRED)
#find_package(X11 REQUIRED)

add_subdirectory(src)
