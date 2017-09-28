cmake_minimum_required(VERSION 3.9)
set(PWD "${CMAKE_CURRENT_SOURCE_DIR}")
INCLUDE (${PWD}/../../../DocumentRoot.cmake)

project(karchive CXX)
# kde compression lib to open zip basd documents
set(PRO_LIBARC_NAME "qt_archive_api")
set(PRO_LIBARCSTATIC_NAME "qt_archive")

set (CMAKE_CXX_STANDARD 11)

include(FeatureSummary)
include(GenerateExportHeader)


find_package( Qt5Core REQUIRED )


find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED)

set(Qt5Core_PRIVATE_INCLUDE_DIRS "")

 # The Qt5Widgets_INCLUDES also includes the include directories for
 # dependencies QtCore and QtGui we link only core 
set(QT_CORE_HEADER  ${QT_INSTALL_PREFIX}/lib/QtCore.framework/Headers)
include_directories(${Qt5Widgets_INCLUDES})
include_directories(${QT_CORE_HEADER})
include_directories(${PWD})
include_directories(${PWD}/io)
set(HACKDIR ${PWD}"/QtCore")

if (UNIX OR APPLE)
    # exec_program(ln  ARGS "-s" ${QT_CORE_HEADER} ${HACKDIR}  OUTPUT_VARIABLE __HACKQT5CORE )
endif()

 # include_directories(${HACKDIR})


set(CMAKE_AUTOMOC OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


find_package(ZLIB)
set_package_properties(ZLIB PROPERTIES
    URL "http://www.zlib.net"
    DESCRIPTION "Support for gzip compressed files and data streams"
    TYPE REQUIRED
    PURPOSE "Required by the core KDE libraries and some criti cal kioslaves"
)

find_package(BZip2)
set_package_properties(BZip2 PROPERTIES
    URL "http://www.bzip.org"
    DESCRIPTION "Support for BZip2 compressed files and data streams"
    TYPE RECOMMENDED
    PURPOSE "Support for BZip2 compressed files and data streams"
)

find_package(LibLZMA)
set_package_properties(LibLZMA PROPERTIES
    URL "http://tukaani.org/xz/"
    DESCRIPTION "Support for xz compressed files and data streams"
    PURPOSE "Support for xz compressed files and data streams"
)
include_directories(
    ${ZLIB_INCLUDE_DIR}
)

# if qt5 have QT_NO_TEMPORARYFILE in qsavefile.cpp build go dead


set(MYLIB_VERSION_MAJOR 5)
set(MYLIB_VERSION_MINOR 2)
set(MYLIB_VERSION_PATCH 0)
set(MYLIB_VERSION_STRING ${MYLIB_VERSION_MAJOR}.${MYLIB_VERSION_MINOR}.${MYLIB_VERSION_PATCH})


set(PROJECT_COMPANY_NAME “KDE5 LIB”)
set(PROJECT_DESCRIPTION “Library to handle ompression file or documents ”)
set(PROJECT_URL "https://www.kde.org/")
string(TIMESTAMP PROJECT_COPYRIGHT "Copyright © 1999-%Y KDE All Rights Reserved." UTC)
set(PROJECT_COPYRIGHT ${PROJECT_COPYRIGHT})



set(HAVE_BZIP2_SUPPORT ${BZIP2_FOUND})
if(BZIP2_FOUND AND BZIP2_NEED_PREFIX)
    set(NEED_BZ2_PREFIX 1)
endif()

set(HAVE_XZ_SUPPORT ${LIBLZMA_FOUND})

configure_file(config-compression.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-compression.h)
add_definitions(-DQT_NO_CAST_FROM_ASCII)

if(BZIP2_FOUND)
    include_directories(${BZIP2_INCLUDE_DIR})
    set(karchive_OPTIONAL_SRCS ${karchive_OPTIONAL_SRCS} kbzip2filter.cpp)
    set(karchive_OPTIONAL_LIBS ${karchive_OPTIONAL_LIBS} ${BZIP2_LIBRARIES})
endif()

if(LIBLZMA_FOUND)
    include_directories(${LIBLZMA_INCLUDE_DIRS})
    set(karchive_OPTIONAL_SRCS ${karchive_OPTIONAL_SRCS} kxzfilter.cpp k7zip.cpp)
    set(karchive_OPTIONAL_LIBS ${karchive_OPTIONAL_LIBS} ${LIBLZMA_LIBRARIES})
endif()


find_package( Qt5Core REQUIRED )

set(CMAKE_AUTOMOC OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)



set(karchive_SRCS
    karchive.cpp
    kar.cpp
    kcompressiondevice.cpp
    kfilterbase.cpp
    kfilterdev.cpp
    kgzipfilter.cpp
    klimitediodevice.cpp
    knonefilter.cpp
    ktar.cpp
    kzip.cpp
    krcc.cpp
)

# if we build app in cmake now not pri file
INCLUDE_DIRECTORIES({PWD}/)

set(CMAKE_BUILD_TYPE Release)


set(PRO_LIBARC_NAME "qt_archive_api")
set(PRO_LIBARCSTATIC_NAME "qt_archive")


file (GLOB Karchive_headers ${PWD}/*.h )

set(QTMODULE " core ")
Generate_PriFile(${CMAKE_INSTALL_PREFIX_0} ${PRO_LIBARCSTATIC_NAME}  "${Karchive_headers}"  ${QTMODULE})


add_library( ${PRO_LIBARC_NAME} SHARED ${karchive_SRCS} ${karchive_OPTIONAL_SRCS} )
target_link_libraries(${PRO_LIBARC_NAME}
    PUBLIC
        Qt5::Core
    PRIVATE
        ${karchive_OPTIONAL_LIBS}
        ${ZLIB_LIBRARY}
)

add_library(${PRO_LIBARCSTATIC_NAME} STATIC ${karchive_SRCS} ${karchive_OPTIONAL_SRCS} )
target_link_libraries(${PRO_LIBARC_NAME}
    PUBLIC
        Qt5::Core
    PRIVATE
        ${karchive_OPTIONAL_LIBS}
        ${ZLIB_LIBRARY}
)

# only SHARED stamp version! 
set_target_properties(${PRO_LIBARC_NAME} PROPERTIES VERSION ${MYLIB_VERSION_STRING} SOVERSION 1)

message(STATUS " Set here include dir on shell result QT_INSTALL_PREFIX e core include file .. " ${QT_CORE_HEADER} )


install(TARGETS ${PRO_LIBARC_NAME} LIBRARY DESTINATION ${DIR_LIBTARGET})
install(TARGETS ${PRO_LIBARCSTATIC_NAME} ARCHIVE DESTINATION ${DIR_LIBTARGET})











