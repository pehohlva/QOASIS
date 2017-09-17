cmake_minimum_required(VERSION 3.9)

get_filename_component(PRO_ROOTDIR
                       "${CMAKE_CURRENT_LIST_DIR}/DocumentRoot.cmake"
				       DIRECTORY)
project(DummyRead CXX)			   
set(PRO_UNIX_NAME "oasispeak")
set(PRO_MACOSX_NAME "OasiSpeaker")

set(SUFFIX "")
if(APPLE)
	set(SUFFIX ".app")
	elseif(WIN32)
	set(SUFFIX ".exe")
endif()

set(APP_NAME_1 ${PRO_MACOSX_NAME}${SUFFIX})


set(CMAKE_INSTALL_PREFIX_0 ${PRO_ROOTDIR}/Applications)
message(STATUS "MESSAGE: ROOT CONFIG IS INCLUDED vars=PRO_ROOTDIR=${PRO_ROOTDIR}")
message(STATUS "MESSAGE: CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX_0}")



set(DIR_LIBTARGET  ${CMAKE_INSTALL_PREFIX_0}/lib)
set(SIGNALAPPBUILD "${CMAKE_INSTALL_PREFIX_0}/lib/libqt_language_detect.a" )

file(MAKE_DIRECTORY ${CMAKE_INSTALL_PREFIX_0})
file(MAKE_DIRECTORY ${DIR_LIBTARGET})

function(_CURRENTDIR_)
  exec_program(pwd  OUTPUT_VARIABLE _PWD_)
  # message(STATUS "MESSAGE: CURRENT DIR BY COMMAND {pwd console} OUT:${_PWD_} function macro DocumentRoot.cmake")
endfunction()
_CURRENTDIR_()



# qmake -query QT_INSTALL_LIBS
#message( "QT_VERSION: $$[QT_VERSION]--")
#message( "QMAKE_MKSPECS: $$[QMAKE_MKSPECS]--")
#message( "QT_INSTALL_LIBS: $$[QT_INSTALL_LIBS]--")
#message( "QT_INSTALL_CONFIGURATION: $$[QT_INSTALL_CONFIGURATION]--")
#message( "QT_INSTALL_DATA: $$[QT_INSTALL_DATA]--")
#message( "QT_INSTALL_DOCS: $$[QT_INSTALL_DOCS]--")
#message( "QT_INSTALL_PLUGINS: $$[QT_INSTALL_PLUGINS]--")
#message( "QT_INSTALL_PREFIX: $$[QT_INSTALL_PREFIX]--")
#message( "QT_INSTALL_TRANSLATIONS: $$[QT_INSTALL_TRANSLATIONS]--")

if (UNIX OR APPLE)
   # qmake -query QT_INSTALL_LIBS
   exec_program(qmake  ARGS "-query" "QT_INSTALL_LIBS"  OUTPUT_VARIABLE __QT_INSTALL_LIBS )
endif()

if(MSVS OR MSYS OR MINGW)
    set(SAYUNAME "WINDOWOS_GENERIC")
	exec_program("qmake.exe"  ARGS "-query" "QT_INSTALL_LIBS"  OUTPUT_VARIABLE __QT_INSTALL_LIBS )
	# detect WINE run cmd vol give 0000-0000
	# window have also way to speech access registry
	add_definitions(-DUNIXCONSOLE_CLOSE)
	add_definitions(-DWINDOWCONSOLE_OPEN)
endif()
set(DIR_LIBQT5  ${__QT_INSTALL_LIBS})

if (EXISTS "${DIR_LIBQT5}")
	message(STATUS "MESSAGE: XXXXXXXXX DIRECTORY QT4/5  ${DIR_LIBQT5} EXIST=TRUE XXXXXXX")
endif()

macro(install_symlink filepath sympath)
    install(CODE "execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ${filepath} ${sympath})")
    install(CODE "message(\"-- Created symlink: ${sympath} -> ${filepath}\")")
endmacro(install_symlink)




# Mac OS X: add homebrew, macports and fink paths, including homebrew Qt and zlib
if(APPLE)
	message(STATUS "Enabling build support for Mac OS X")
	set(CMAKE_PREFIX_PATH  "${DIR_LIBTARGET};/Users/dev/Applications/qt5.9.1;/usr/local/lib;/opt/local/lib;/sw/lib;${CMAKE_PREFIX_PATH}")
	set(CMAKE_INCLUDE_PATH "${DIR_LIBTARGET};/Users/dev/Applications/qt5.9.1;/usr/local/include;/usr/local/opt/zlib;/opt/local/include;/sw/include;${CMAKE_INCLUDE_PATH}")
	set(CMAKE_LIBRARY_PATH "${DIR_LIBTARGET};/Users/dev/Applications/qt5.9.1/lib;/usr/local/lib;/usr/local/opt/zlib;/opt/local/lib;/sw/lib;${CMAKE_LIBRARY_PATH}")
	set(CMAKE_PROGRAM_PATH "/Users/dev/Applications/qt5.9.1/bin;/usr/local/bin;/opt/local/bin;/sw/bin;${CMAKE_PROGRAM_PATH}")
	include_directories("/usr/local/include" "/usr/local/opt/zlib/include" "/opt/local/include" "/sw/include")
	# only include dirs that exist or warnings are generated
	foreach(link_dir "/usr/local/lib" "/usr/local/opt/qt5/lib" "/usr/local/opt/zlib/lib" "/opt/local/lib" "/sw/lib")
		if(EXISTS ${link_dir} AND IS_DIRECTORY ${link_dir})
			link_directories(${link_dir})
		endif()
	endforeach()
endif()










