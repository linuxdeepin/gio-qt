# Populate a CMake variable with the sources
# TODO: portable headers?
set (QGIO_PUBLIC_HEADER_FILES
    dgiovolumemanager.h
    dgiomount.h
    dgiovolume.h
    dgiofile.h
)

set (QGIO_PRIVATE_CPP_FILES
    dgiovolumemanager.cpp
    dgiomount.cpp
    dgiovolume.cpp
    dgiofile.cpp
)

# Library
add_library (gio-qt STATIC
    ${QGIO_PUBLIC_HEADER_FILES}
    ${QGIO_PRIVATE_CPP_FILES}
)

target_include_directories(gio-qt
PRIVATE
    ${GTKMM_INCLUDE_DIRS}
PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries (gio-qt Qt5::Core ${GTKMM_LIBRARIES})

target_compile_definitions(gio-qt PRIVATE
    QT_NO_KEYWORDS
)
