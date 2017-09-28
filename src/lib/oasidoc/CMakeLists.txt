cmake_minimum_required(VERSION 3.9)
# THIS IS OASIDOC DIR ALL LIB TO CONVERT DOCUMENT!
set(PWD "${CMAKE_CURRENT_SOURCE_DIR}")
INCLUDE (${PWD}/../../../DocumentRoot.cmake)

project(OASIDOC C CXX)
set(PRO_LIBOASIDOC_NAME "qt_oasidocuments_api")
set(PRO_STATIC_LIBOASIDOC_NAME "qt_oasidocuments")
set(MYLIB_VERSION_MAJOR 1)
set(MYLIB_VERSION_MINOR 6)
set(MYLIB_VERSION_PATCH 0)
set(MYLIB_VERSION_STRING ${MYLIB_VERSION_MAJOR}.${MYLIB_VERSION_MINOR}.${MYLIB_VERSION_PATCH})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
INCLUDE(CheckFunctionExists)
INCLUDE(CheckIncludeFiles)
INCLUDE(CheckSymbolExists)
INCLUDE(CheckTypeSize)
INCLUDE(CheckCSourceRuns)
INCLUDE(CheckCSourceCompiles)
INCLUDE(CheckStructHasMember)
INCLUDE(TestBigEndian)

CHECK_FUNCTION_EXISTS(_chmod HAVE__CHMOD)
CHECK_FUNCTION_EXISTS(_open HAVE__OPEN)
CHECK_FUNCTION_EXISTS(open HAVE_OPEN)


find_package( ZLIB REQUIRED )
if ( ZLIB_FOUND )
    include_directories( ${ZLIB_INCLUDE_DIRS} )
endif( ZLIB_FOUND )




find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )
find_package( Qt5Xml REQUIRED )


set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

INCLUDE_DIRECTORIES({PWD}/)
INCLUDE_DIRECTORIES(${PWD}/ooo)
INCLUDE_DIRECTORIES(${PWD}/epub)
INCLUDE_DIRECTORIES(${PWD}/zlib)

set(CMAKE_BUILD_TYPE Release)


set(Current_Public_HEADERS
	${PWD}/ooo/converter.h
	${PWD}/epub/edocument.h
	${PWD}/rtf-qt/rtfreader.h
	${PWD}/zlib/gzlib.h
    Current_Public_HEADERS
)

list(APPEND OASIDOC_SOURCES
          ${PWD}/kzip.cpp 
          ${PWD}/QmyDom.cpp 
          ${PWD}/core_htmldriver.cpp 
          ${PWD}/epub/econverter.cpp 
          ${PWD}/epub/edocument.cpp 
          ${PWD}/ooo/converter.cpp 
          ${PWD}/ooo/document.cpp 
          ${PWD}/ooo/formatproperty.cpp 
           ${PWD}/ooo/manifest.cpp 
           ${PWD}/ooo/styleinformation.cpp 
           ${PWD}/ooo/styleparser.cpp
           ${PWD}/rtf-qt/TextDocumentRtfOutput.cpp
           ${PWD}/rtf-qt/AbstractRtfOutput.cpp
           ${PWD}/rtf-qt/AuthorPcdataDestination.cpp
           ${PWD}/rtf-qt/CategoryPcdataDestination.cpp
           ${PWD}/rtf-qt/ColorTableDestination.cpp
           ${PWD}/rtf-qt/CommentPcdataDestination.cpp
           ${PWD}/rtf-qt/CompanyPcdataDestination.cpp
           ${PWD}/rtf-qt/controlword.cpp
           ${PWD}/rtf-qt/Destination.cpp
           ${PWD}/rtf-qt/DocumentCommentPcdataDestination.cpp
           ${PWD}/rtf-qt/DocumentDestination.cpp
           ${PWD}/rtf-qt/FontTableDestination.cpp
           ${PWD}/rtf-qt/GeneratorPcdataDestination.cpp
           ${PWD}/rtf-qt/HLinkBasePcdataDestination.cpp
           ${PWD}/rtf-qt/IgnoredDestination.cpp
           ${PWD}/rtf-qt/InfoCreatedTimeDestination.cpp
           ${PWD}/rtf-qt/InfoDestination.cpp
           ${PWD}/rtf-qt/InfoPrintedTimeDestination.cpp
           ${PWD}/rtf-qt/InfoRevisedTimeDestination.cpp
           ${PWD}/rtf-qt/InfoTimeDestination.cpp
           ${PWD}/rtf-qt/KeywordsPcdataDestination.cpp
           ${PWD}/rtf-qt/ManagerPcdataDestination.cpp
           ${PWD}/rtf-qt/OperatorPcdataDestination.cpp
           ${PWD}/rtf-qt/PcdataDestination.cpp
           ${PWD}/rtf-qt/PictDestination.cpp
           ${PWD}/rtf-qt/rtfreader.cpp
           ${PWD}/rtf-qt/StyleSheetDestination.cpp
           ${PWD}/rtf-qt/SubjectPcdataDestination.cpp
           ${PWD}/rtf-qt/TitlePcdataDestination.cpp
           ${PWD}/rtf-qt/Token.cpp
           ${PWD}/rtf-qt/Tokenizer.cpp
           ${PWD}/rtf-qt/UserPropsDestination.cpp
)


if(MINGW)   
	list(APPEND OASIDOC_SOURCES   
${PWD}/zlib/adler32.c
${PWD}/zlib/compress.c
${PWD}/zlib/crc32.c
${PWD}/zlib/deflate.c
${PWD}/zlib/gzclose.c
${PWD}/zlib/gzlib.c
${PWD}/zlib/gzread.c
${PWD}/zlib/gzwrite.c
${PWD}/zlib/infback.c
${PWD}/zlib/inffast.c
${PWD}/zlib/inflate.c
${PWD}/zlib/inftrees.c
${PWD}/zlib/trees.c
${PWD}/zlib/uncompr.c
${PWD}/zlib/zutil.c
)
endif()




set(QTMODULE " core gui xml widgets ")
Generate_PriFile(${CMAKE_INSTALL_PREFIX_0} ${PRO_STATIC_LIBOASIDOC_NAME}  "${Current_Public_HEADERS}"  ${QTMODULE})






add_library(${PRO_LIBOASIDOC_NAME} SHARED ${OASIDOC_SOURCES})
qt5_use_modules(${PRO_LIBOASIDOC_NAME} Core Widgets Gui Xml )
if(APPLE)
target_link_libraries( ${PRO_LIBOASIDOC_NAME} ${ZLIB_LIBRARIES} )
endif()
set_target_properties(${PRO_LIBOASIDOC_NAME} PROPERTIES VERSION ${MYLIB_VERSION_STRING} SOVERSION 1)

add_library(${PRO_STATIC_LIBOASIDOC_NAME} STATIC ${OASIDOC_SOURCES})
if(APPLE)
target_link_libraries( ${PRO_STATIC_LIBOASIDOC_NAME} ${ZLIB_LIBRARIES} )
endif()
qt5_use_modules(${PRO_STATIC_LIBOASIDOC_NAME} Core Widgets Gui Xml )

install(TARGETS ${PRO_LIBOASIDOC_NAME} LIBRARY DESTINATION ${DIR_LIBTARGET})
install(TARGETS ${PRO_STATIC_LIBOASIDOC_NAME} ARCHIVE DESTINATION ${DIR_LIBTARGET})

