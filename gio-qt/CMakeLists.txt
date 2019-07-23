# Populate a CMake variable with the sources
# TODO: portable headers?

# Some custom variables
set(DEST_DIR "${CMAKE_INSTALL_PREFIX}")

CONFIGURE_FILE("gio-qt.pc.in" "gio-qt.pc" @ONLY)

set (QGIO_PUBLIC_HEADER_FILES
    dgiovolumemanager.h
    dgiomountoperation.h
    dgiomount.h
    dgiovolume.h
    dgiofile.h
    dgiofileinfo.h
)

set (QGIO_PRIVATE_CPP_FILES
    dgiovolumemanager.cpp
    dgiomountoperation.cpp
    dgiomount.cpp
    dgiovolume.cpp
    dgiofile.cpp
    dgiofileinfo.cpp
)

# Library
add_library (gio-qt STATIC
    ${QGIO_PUBLIC_HEADER_FILES}
    ${QGIO_PRIVATE_CPP_FILES}
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

install (TARGETS gio-qt DESTINATION lib)

install (FILES "${CMAKE_CURRENT_BINARY_DIR}/gio-qt.pc"
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig
)
