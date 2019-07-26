# Populate a CMake variable with the sources
# TODO: portable headers?

configure_file ("gio-qt.pc.in" "gio-qt.pc" @ONLY)

set (QGIO_PUBLIC_HEADER_FILES
    dgiovolumemanager.h
    dgiomountoperation.h
    dgiomount.h
    dgiovolume.h
    dgiofile.h
    dgiofileinfo.h
    dgioutils.h
)

set (QGIO_PRIVATE_CPP_FILES
    dgiovolumemanager.cpp
    dgiomountoperation.cpp
    dgiomount.cpp
    dgiovolume.cpp
    dgiofile.cpp
    dgiofileinfo.cpp
    dgioutils.cpp
)

# Library
add_library (gio-qt SHARED
    ${QGIO_PUBLIC_HEADER_FILES}
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
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
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
