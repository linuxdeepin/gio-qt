# Populate a CMake variable with the sources
# TODO: portable headers?
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

target_link_libraries (gio-qt Qt5::Core ${GTKMM_LIBRARIES})

target_compile_definitions(gio-qt PRIVATE
    QT_NO_KEYWORDS
)
