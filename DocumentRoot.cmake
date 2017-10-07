cmake_minimum_required(VERSION 3.1)

get_filename_component(PRO_ROOTDIR
                       "${CMAKE_CURRENT_LIST_DIR}/DocumentRoot.cmake"
				       DIRECTORY)
project(DummyRead CXX)			   
set(PRO_UNIX_NAME "oasispeak")
set(PRO_MACOSX_NAME "OasiSpeaker")


# setup to find the last hidden lib or module version
set(CMAKE_MODULE_PATH "${PRO_ROOTDIR}/src/app/cmake")


# super method from kde lib to create qmake file.pri to include
include(ECMGeneratePriFile)


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
   exec_program(qmake  ARGS "-query" "QT_INSTALL_PREFIX"  OUTPUT_VARIABLE __QT_BASEDIR )
endif()

if(MSVS OR MSYS OR MINGW)
    set(SAYUNAME "WINDOWOS_GENERIC")
	exec_program("qmake.exe"  ARGS "-query" "QT_INSTALL_LIBS"  OUTPUT_VARIABLE __QT_INSTALL_LIBS )
	exec_program("qmake.exe"  ARGS "-query" "QT_INSTALL_PREFIX"  OUTPUT_VARIABLE __QT_BASEDIR )
	# detect WINE run cmd vol give 0000-0000 qmake -query QT_INSTALL_PREFIX
	# window have also way to speech access registry
	add_definitions(-DUNIXCONSOLE_CLOSE)
	add_definitions(-DWINDOWCONSOLE_OPEN)
endif()
set(DIR_LIBQT5  ${__QT_INSTALL_LIBS})
set(QT_INSTALL_PREFIX  ${__QT_BASEDIR})

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
	foreach(link_dir "/usr/local/lib" "/usr/local/opt/zlib/lib" "/opt/local/lib" "/sw/lib")
		if(EXISTS ${link_dir} AND IS_DIRECTORY ${link_dir})
			link_directories(${link_dir})
		endif()
	endforeach()
endif()


# ------------------------- Begin Generic CMake Variable Logging ------------------

# /*	C++ comment style not allowed	*/


# if you are building in-source, this is the same as CMAKE_SOURCE_DIR, otherwise 
# this is the top level directory of your build tree 
MESSAGE( STATUS "CMAKE_BINARY_DIR:         " ${CMAKE_BINARY_DIR} )

# if you are building in-source, this is the same as CMAKE_CURRENT_SOURCE_DIR, otherwise this 
# is the directory where the compiled or generated files from the current CMakeLists.txt will go to 
MESSAGE( STATUS "CMAKE_CURRENT_BINARY_DIR: " ${CMAKE_CURRENT_BINARY_DIR} )

# this is the directory, from which cmake was started, i.e. the top level source directory 
MESSAGE( STATUS "CMAKE_SOURCE_DIR:         " ${CMAKE_SOURCE_DIR} )

# this is the directory where the currently processed CMakeLists.txt is located in 
MESSAGE( STATUS "CMAKE_CURRENT_SOURCE_DIR: " ${CMAKE_CURRENT_SOURCE_DIR} )

# contains the full path to the top level directory of your build tree 
MESSAGE( STATUS "PROJECT_BINARY_DIR: " ${PROJECT_BINARY_DIR} )

# contains the full path to the root of your project source directory,
# i.e. to the nearest directory where CMakeLists.txt contains the PROJECT() command 
MESSAGE( STATUS "PROJECT_SOURCE_DIR: " ${PROJECT_SOURCE_DIR} )

# set this variable to specify a common place where CMake should put all executable files
# (instead of CMAKE_CURRENT_BINARY_DIR)
MESSAGE( STATUS "EXECUTABLE_OUTPUT_PATH: " ${EXECUTABLE_OUTPUT_PATH} )

# set this variable to specify a common place where CMake should put all libraries 
# (instead of CMAKE_CURRENT_BINARY_DIR)
MESSAGE( STATUS "LIBRARY_OUTPUT_PATH:     " ${LIBRARY_OUTPUT_PATH} )

# tell CMake to search first in directories listed in CMAKE_MODULE_PATH
# when you use FIND_PACKAGE() or INCLUDE()
MESSAGE( STATUS "CMAKE_MODULE_PATH: " ${CMAKE_MODULE_PATH} )

# this is the complete path of the cmake which runs currently (e.g. /usr/local/bin/cmake) 
MESSAGE( STATUS "CMAKE_COMMAND: " ${CMAKE_COMMAND} )

# this is the CMake installation directory 
MESSAGE( STATUS "CMAKE_ROOT: " ${CMAKE_ROOT} )

# this is the filename including the complete path of the file where this variable is used. 
MESSAGE( STATUS "CMAKE_CURRENT_LIST_FILE: " ${CMAKE_CURRENT_LIST_FILE} )

# this is linenumber where the variable is used
MESSAGE( STATUS "CMAKE_CURRENT_LIST_LINE: " ${CMAKE_CURRENT_LIST_LINE} )

# this is used when searching for include files e.g. using the FIND_PATH() command.
MESSAGE( STATUS "CMAKE_INCLUDE_PATH: " ${CMAKE_INCLUDE_PATH} )

# this is used when searching for libraries e.g. using the FIND_LIBRARY() command.
MESSAGE( STATUS "CMAKE_LIBRARY_PATH: " ${CMAKE_LIBRARY_PATH} )

# the complete system name, e.g. "Linux-2.4.22", "FreeBSD-5.4-RELEASE" or "Windows 5.1" 
MESSAGE( STATUS "CMAKE_SYSTEM: " ${CMAKE_SYSTEM} )

# the short system name, e.g. "Linux", "FreeBSD" or "Windows"
MESSAGE( STATUS "CMAKE_SYSTEM_NAME: " ${CMAKE_SYSTEM_NAME} )

# only the version part of CMAKE_SYSTEM 
MESSAGE( STATUS "CMAKE_SYSTEM_VERSION: " ${CMAKE_SYSTEM_VERSION} )

# the processor name (e.g. "Intel(R) Pentium(R) M processor 2.00GHz") 
MESSAGE( STATUS "CMAKE_SYSTEM_PROCESSOR: " ${CMAKE_SYSTEM_PROCESSOR} )

# is TRUE on all UNIX-like OS's, including Apple OS X and CygWin
MESSAGE( STATUS "UNIX: " ${UNIX} )

# is TRUE on Windows, including CygWin 
MESSAGE( STATUS "WIN32: " ${WIN32} )

# is TRUE on Apple OS X
MESSAGE( STATUS "APPLE: " ${APPLE} )

# is TRUE when using the MinGW compiler in Windows
MESSAGE( STATUS "MINGW: " ${MINGW} )

# is TRUE on Windows when using the CygWin version of cmake
MESSAGE( STATUS "CYGWIN: " ${CYGWIN} )

# is TRUE on Windows when using a Borland compiler 
MESSAGE( STATUS "BORLAND: " ${BORLAND} )

# Microsoft compiler 
MESSAGE( STATUS "MSVC: " ${MSVC} )
MESSAGE( STATUS "MSVC_IDE: " ${MSVC_IDE} )
MESSAGE( STATUS "MSVC60: " ${MSVC60} )
MESSAGE( STATUS "MSVC70: " ${MSVC70} )
MESSAGE( STATUS "MSVC71: " ${MSVC71} )
MESSAGE( STATUS "MSVC80: " ${MSVC80} )
MESSAGE( STATUS "CMAKE_COMPILER_2005: " ${CMAKE_COMPILER_2005} )


# set this to true if you don't want to rebuild the object files if the rules have changed, 
# but not the actual source files or headers (e.g. if you changed the some compiler switches) 
MESSAGE( STATUS "CMAKE_SKIP_RULE_DEPENDENCY: " ${CMAKE_SKIP_RULE_DEPENDENCY} )

# since CMake 2.1 the install rule depends on all, i.e. everything will be built before installing. 
# If you don't like this, set this one to true.
MESSAGE( STATUS "CMAKE_SKIP_INSTALL_ALL_DEPENDENCY: " ${CMAKE_SKIP_INSTALL_ALL_DEPENDENCY} )

# If set, runtime paths are not added when using shared libraries. Default it is set to OFF
MESSAGE( STATUS "CMAKE_SKIP_RPATH: " ${CMAKE_SKIP_RPATH} )

# set this to true if you are using makefiles and want to see the full compile and link 
# commands instead of only the shortened ones 
MESSAGE( STATUS "CMAKE_VERBOSE_MAKEFILE: " ${CMAKE_VERBOSE_MAKEFILE} )

# this will cause CMake to not put in the rules that re-run CMake. This might be useful if 
# you want to use the generated build files on another machine. 
MESSAGE( STATUS "CMAKE_SUPPRESS_REGENERATION: " ${CMAKE_SUPPRESS_REGENERATION} )


# A simple way to get switches to the compiler is to use ADD_DEFINITIONS(). 
# But there are also two variables exactly for this purpose: 

# the compiler flags for compiling C sources 
MESSAGE( STATUS "CMAKE_C_FLAGS: " ${CMAKE_C_FLAGS} )

# the compiler flags for compiling C++ sources 
MESSAGE( STATUS "CMAKE_CXX_FLAGS: " ${CMAKE_CXX_FLAGS} )


# Choose the type of build.  Example: SET(CMAKE_BUILD_TYPE Debug) 
MESSAGE( STATUS "CMAKE_BUILD_TYPE: " ${CMAKE_BUILD_TYPE} )

# if this is set to ON, then all libraries are built as shared libraries by default.
MESSAGE( STATUS "BUILD_SHARED_LIBS: " ${BUILD_SHARED_LIBS} )

# the compiler used for C files 
MESSAGE( STATUS "CMAKE_C_COMPILER: " ${CMAKE_C_COMPILER} )

# the compiler used for C++ files 
MESSAGE( STATUS "CMAKE_CXX_COMPILER: " ${CMAKE_CXX_COMPILER} )

# if the compiler is a variant of gcc, this should be set to 1 
MESSAGE( STATUS "CMAKE_COMPILER_IS_GNUCC: " ${CMAKE_COMPILER_IS_GNUCC} )

# if the compiler is a variant of g++, this should be set to 1 
MESSAGE( STATUS "CMAKE_COMPILER_IS_GNUCXX : " ${CMAKE_COMPILER_IS_GNUCXX} )

# the tools for creating libraries 
MESSAGE( STATUS "CMAKE_AR: " ${CMAKE_AR} )
MESSAGE( STATUS "CMAKE_RANLIB: " ${CMAKE_RANLIB} )

#
#MESSAGE( STATUS ": " ${} )

# ------------------------- End of Generic CMake Variable Logging ------------------










