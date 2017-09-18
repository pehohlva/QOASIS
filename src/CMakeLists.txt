cmake_minimum_required(VERSION 3.6)
set(PWD "${CMAKE_CURRENT_SOURCE_DIR}")
INCLUDE (${PWD}/../DocumentRoot.cmake)
project(Oasi_SDK  CXX)
set(PRO_LIBTESTAPP "oasi_api")

find_package( Qt5Core REQUIRED )

set(CMAKE_BUILD_TYPE Release)

# APPEND ANY LIB NEED TO THIS PROJECT HERE!
add_subdirectory( ${PWD}/lib/qcld2 )
add_subdirectory( ${PWD}/lib/oasidoc )
set( EXTRA_LIBS ${EXTRA_LIBS} qt_oasidocuments_api )
set( EXTRA_LIBS ${EXTRA_LIBS} qt_language_detect_api )

INCLUDE_DIRECTORIES(${PWD}/lib/qcld2/include_cld2)

# ONLY LANGUAGE DETECT LIB IS 1,8M 14 Set 14:11 oasi_api
add_executable( ${PRO_LIBTESTAPP} ${PWD}/libapi.cpp )
qt5_use_modules(${PRO_LIBTESTAPP} Core Widgets Gui Xml )
target_link_libraries( ${PRO_LIBTESTAPP} ${EXTRA_LIBS} )

if (UNIX OR APPLE)
	if (EXISTS ${SIGNALAPPBUILD})
	if (APPLE)
	FILE(GLOB inlibs RELATIVE "${DIR_LIBTARGET}" "${DIR_LIBTARGET}/libqt_*")
    elseif(UNIX)
	FILE(GLOB inlibs RELATIVE "${DIR_LIBTARGET}" "${DIR_LIBTARGET}/libqt_*")
    endif()
	
	FOREACH(infileName ${inlibs})
		set(LIBFULLEXIST ${DIR_LIBTARGET}/${infileName} )
		set(LIBVIRTUALQT ${DIR_LIBQT5}/${infileName} )
		if (EXISTS ${LIBVIRTUALQT})
		file(REMOVE ${LIBVIRTUALQT})
		endif()
		install_symlink( ${LIBFULLEXIST} ${LIBVIRTUALQT} )
    ENDFOREACH(infileName)
    endif()
endif()

message("END OF CREATE ALL LIBS NEED BY THIS PROJECT.... Test run:  ./${PRO_LIBTESTAPP} ")






