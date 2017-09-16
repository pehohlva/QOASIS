cmake_minimum_required(VERSION 3.9)
set(PWD "${CMAKE_CURRENT_SOURCE_DIR}")
INCLUDE (${PWD}/../../../DocumentRoot.cmake)

project(QTCLD2 CXX)
# THIS IS QCLD2 DIR LIB TO DETECT LANGUAGE FROM DOCUMENT & TEXT!
set(PRO_LIBCLD2_NAME "qt_language_detect_api")
set(PRO_LIBCLD2STATIC_NAME "qt_language_detect")

set(MYLIB_VERSION_MAJOR 2)
set(MYLIB_VERSION_MINOR 9)
set(MYLIB_VERSION_PATCH 0)
set(MYLIB_VERSION_STRING ${MYLIB_VERSION_MAJOR}.${MYLIB_VERSION_MINOR}.${MYLIB_VERSION_PATCH})


set(PROJECT_COMPANY_NAME “Avasoft Switzerland”)
set(PROJECT_DESCRIPTION “Simple Library to detect over 200 Language from Text or document. ”)
set(PROJECT_URL "https://www.qt.io/")
string(TIMESTAMP PROJECT_COPYRIGHT "Copyright © 1999-%Y P.Kopp All Rights Reserved." UTC)
set(PROJECT_COPYRIGHT ${PROJECT_COPYRIGHT})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

find_package( Qt5Core REQUIRED )

set(CMAKE_AUTOMOC OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

INCLUDE_DIRECTORIES({PWD}/)
INCLUDE_DIRECTORIES(${PWD}/source_cld2)
INCLUDE_DIRECTORIES(${PWD}/include_cld2)

set(CMAKE_BUILD_TYPE Release)

file (GLOB SRC_FILES ${PWD}/source_cld2/*.cpp ${PWD}/source_cld2/*.cc  )

add_library(${PRO_LIBCLD2_NAME} SHARED ${SRC_FILES})
# qt5_use_modules(${PRO_LIBCLD2_NAME} Qt5Core )
target_link_libraries(${PRO_LIBCLD2_NAME} Qt5::Core)

add_library(${PRO_LIBCLD2STATIC_NAME} STATIC ${SRC_FILES})
# qt5_use_modules(${PRO_LIBCLD2_NAME} Qt5Core )
target_link_libraries(${PRO_LIBCLD2STATIC_NAME} Qt5::Core)
# only SHARED stamp version! 
set_target_properties(${PRO_LIBCLD2_NAME} PROPERTIES VERSION ${MYLIB_VERSION_STRING} SOVERSION 1)


install(TARGETS ${PRO_LIBCLD2_NAME} LIBRARY DESTINATION ${DIR_LIBTARGET})
install(TARGETS ${PRO_LIBCLD2STATIC_NAME} ARCHIVE DESTINATION ${DIR_LIBTARGET})










