project(gio-qt)

cmake_minimum_required(VERSION 3.9.5)

option(BUILD_UTILS "Build utilities" ON)

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "-g -Wall")
set(QT_MINIMUM_VERSION "5.6.3")

# Find the QtWidgets library
find_package(Qt5 ${QT_MINIMUM_VERSION} CONFIG REQUIRED Core)
find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-3.0) # look into FindPkgConfig.cmake, 

add_subdirectory (gio-qt)

if (BUILD_UTILS)
    add_subdirectory(qgio-tools)
endif()
