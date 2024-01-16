project(gio-qt)

cmake_minimum_required(VERSION 3.12.4)

option(BUILD_TESTS "Build tests" OFF)
option(BUILD_UTILS "Build utilities" ON)
option(BUILD_DOCS "Build documentation" ON)
option(FORCE_QT5 "Ignore Qt6 when found." OFF)

# Version
if (NOT PROJECT_VERSION)
    set(PROJECT_VERSION "0.1.0")
endif()

if (NOT PROJECT_VERSION_MAJOR)
    set(PROJECT_VERSION_MAJOR 0)
endif()

# Find includes in corresponding build directories
set(CMAKE_INCLUDE_CURRENT_DIR ON)
# Instruct CMake to run moc automatically when needed
set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_FLAGS "-g -Wall")
set(QT5_MINIMUM_VERSION "5.15.0")

# Install settings
if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
    set(CMAKE_INSTALL_PREFIX /usr)
endif ()

include(GNUInstallDirs)

# Find the Qt library
if (NOT FORCE_QT5)
  find_package(Qt6 COMPONENTS Core)
endif()
if(Qt6_FOUND)
  message(STATUS "Using Qt6")
else()
  find_package(Qt5 ${QT5_MINIMUM_VERSION} COMPONENTS Core)
  if(Qt5_FOUND)
    message(STATUS "Using Qt5")
  endif()
endif()
if(NOT Qt${QT_DEFAULT_MAJOR_VERSION}_FOUND)
  message(FATAL_ERROR "Qt6 or Qt5 >= ${QT5_MINIMUM_VERSION} are required.")
endif()

find_package(PkgConfig REQUIRED)
find_package(Doxygen)

pkg_check_modules(GIOMM giomm-2.4) # look into FindPkgConfig.cmake

add_subdirectory (gio-qt)

if (BUILD_TESTS)
    find_package(Qt${QT_DEFAULT_MAJOR_VERSION} COMPONENTS Test REQUIRED)
    add_subdirectory(test)
endif ()

if (BUILD_UTILS)
    add_subdirectory(qgio-tools)
endif ()

if (BUILD_DOCS)
    if (NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is required to build the documentation.")
    endif ()

    set (DOXYGEN_GENERATE_HTML YES)
    set (DOXYGEN_GENERATE_QHP YES)
    set (DOXYGEN_EXTRACT_STATIC YES)
    set (DOXYGEN_OUTPUT_DIRECTORY "./docs/")
    set (DOXYGEN_EXCLUDE_SYMBOLS "*Private;*Test")
    set (DOXYGEN_QHG_LOCATION "qhelpgenerator")
    set (DOXYGEN_QHP_NAMESPACE "org.deepin.gio-qt")
    set (DOXYGEN_QCH_FILE "../gio-qt.qch")
    set (DOXYGEN_QHP_VIRTUAL_FOLDER "gio-qt")

    doxygen_add_docs(doxygen
        ${CMAKE_CURRENT_SOURCE_DIR}/gio-qt
        ALL
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/gio-qt
        COMMENT "Generate documentation via Doxygen"
    )

    install (FILES ${CMAKE_CURRENT_BINARY_DIR}/docs/gio-qt.qch DESTINATION share/qt${QT_DEFAULT_MAJOR_VERSION}/doc)

else ()
    message (STATUS "")
    message (STATUS "To build docs, please use -DBUILD_DOCS=Yes")
    message (STATUS "")
endif()
