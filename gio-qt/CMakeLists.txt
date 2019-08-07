# Populate a CMake variable with the sources
# TODO: portable headers?

configure_file ("gio-qt.pc.in" "gio-qt.pc" @ONLY)

set (QGIO_PUBLIC_HEADER_FILES
    include/dglibutils.h
    include/dgiovolumemanager.h
    include/dgiomountoperation.h
    include/dgiomount.h
    include/dgiovolume.h
    include/dgiofile.h
    include/dgiofileinfo.h
    include/dgiofileiterator.h
    include/dgiodrive.h
    include/dgiosettings.h
)

set (QGIO_PRIVATE_HEADER_FILES
    private/dgiohelper.h
)

set (QGIO_PRIVATE_CPP_FILES
    source/dglibutils.cpp
    source/dgiovolumemanager.cpp
    source/dgiomountoperation.cpp
    source/dgiomount.cpp
    source/dgiovolume.cpp
    source/dgiofile.cpp
    source/dgiofileinfo.cpp
    source/dgiofileiterator.cpp
    source/dgiodrive.cpp
    source/dgiosettings.cpp
    private/dgiohelper.cpp
)

# Library
add_library (gio-qt SHARED
    ${QGIO_PUBLIC_HEADER_FILES}
    ${QGIO_PRIVATE_HEADER_FILES}
    ${QGIO_PRIVATE_CPP_FILES}
)

set_target_properties(
    gio-qt PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR}
)

target_include_directories(gio-qt
PRIVATE
    ${GIOMM_INCLUDE_DIRS}
    ${CMAKE_CURRENT_LIST_DIR}/private
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}/include
)

target_link_libraries (gio-qt Qt5::Core ${GIOMM_LIBRARIES})

target_compile_definitions(gio-qt PRIVATE
    QT_NO_KEYWORDS
)

## dev files
install (FILES ${QGIO_PUBLIC_HEADER_FILES}
    DESTINATION include/gio-qt
)

install_targets ("/${CMAKE_INSTALL_LIBDIR}" gio-qt)

install (FILES "${CMAKE_CURRENT_BINARY_DIR}/gio-qt.pc"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)
