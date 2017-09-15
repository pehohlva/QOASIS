cmake_minimum_required(VERSION 3.6)
project(Oasi_SDK  CXX)
set(PRO_ROOTLIB_NAME "oasi_api")

set(CURRENT_VERSION “2.1.0”)
set(PROJECT_COMPANY_NAME “Avasoft Switzerland”)
set(PROJECT_DESCRIPTION “Main to use linked e build shared lib on dir ./lib”)
set(PROJECT_URL "https://www.qt.io/")
string(TIMESTAMP PROJECT_COPYRIGHT "Copyright © 1999-%Y P.Kopp All Rights Reserved." UTC)
set(PROJECT_COPYRIGHT ${PROJECT_COPYRIGHT})


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# qmake style to copy file from pri qt5 only replace ${PWD}
set(PWD "${CMAKE_CURRENT_SOURCE_DIR}") 
message("Init read Lib Root ${PRO_ROOTLIB_NAME} ")

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)


find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )
find_package( Qt5Xml REQUIRED )



set(CMAKE_BUILD_TYPE Release)
set(LIB_TARGET_CURRENT ${PWD}/lib/)
set(LIB_ST_TARGET_CURRENT ${PWD}/libs/) 

# APPEND ANY LIB NEED TO THIS PROJECT HERE!
add_subdirectory( ${PWD}/lib/qcld2 )
add_subdirectory( ${PWD}/lib/oasidoc )
set( EXTRA_LIBS ${EXTRA_LIBS} qt_oasidocuments_api )
set( EXTRA_LIBS ${EXTRA_LIBS} qt_language_detect_api )


INCLUDE_DIRECTORIES(${PWD}/lib/qcld2/include_cld2)


# ONLY LANGUAGE DETECT LIB IS 1,8M 14 Set 14:11 oasi_api
add_executable( ${PRO_ROOTLIB_NAME} ${PWD}/libapi.cpp )
qt5_use_modules(${PRO_ROOTLIB_NAME} Core Widgets Gui Xml )
target_link_libraries( ${PRO_ROOTLIB_NAME} ${EXTRA_LIBS} )

message("End crate Lib Root ${PRO_ROOTLIB_NAME} ")


# add_subdirectory( ${PWD}/app )






