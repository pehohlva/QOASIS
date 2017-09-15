
# THIS IS OASIDOC DIR ALL LIB TO CONVERT DOCUMENT!
project(OASIDOC C CXX)
set(PRO_LIBOASIDOC_NAME "qt_oasidocuments_api")
set(MYLIB_VERSION_MAJOR 1)
set(MYLIB_VERSION_MINOR 6)
set(MYLIB_VERSION_PATCH 0)
set(MYLIB_VERSION_STRING ${MYLIB_VERSION_MAJOR}.${MYLIB_VERSION_MINOR}.${MYLIB_VERSION_PATCH})

set(PROJECT_COMPANY_NAME “Avasoft Switzerland”)
set(PROJECT_DESCRIPTION “Simple convert various format of Document to HTML also display on QTextEdit Widged from QT5, Read RTF,RTFD,ODT,EPUB Format.”)
set(PROJECT_URL "https://www.qt.io/")
string(TIMESTAMP PROJECT_COPYRIGHT "Copyright © 1999-%Y P.Kopp All Rights Reserved." UTC)
set(PROJECT_COPYRIGHT ${PROJECT_COPYRIGHT})



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# qmake style to copy file from pri qt5 only replace ${PWD}
set(PWD "${CMAKE_CURRENT_SOURCE_DIR}") 
message("Init read google ${PRO_LIBOASIDOC_NAME} file source e header.")


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



find_package( Qt5Core REQUIRED )
find_package( Qt5Widgets REQUIRED )
find_package( Qt5Gui REQUIRED )
find_package( Qt5Xml REQUIRED )

FIND_PACKAGE(BZip2)
IF(BZIP2_FOUND)
  SET (HAVE_LIBBZ2 1)

  INCLUDE_DIRECTORIES(${BZIP2_INCLUDE_DIR})
  SET (OPTIONAL_LIBRARY ${BZIP2_LIBRARY})
ENDIF(BZIP2_FOUND)


set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

INCLUDE_DIRECTORIES({PWD}/)
INCLUDE_DIRECTORIES(${PWD}/ooo)
INCLUDE_DIRECTORIES(${PWD}/epub)
INCLUDE_DIRECTORIES(${PWD}/zlib)

set(CMAKE_BUILD_TYPE Release)

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




add_library(${PRO_LIBOASIDOC_NAME} SHARED ${OASIDOC_SOURCES})
# qt5_use_modules(${PRO_LIBOASIDOC_NAME} Qt5Core )
qt5_use_modules(${PRO_LIBOASIDOC_NAME} Core Widgets Gui Xml )
# TARGET_LINK_LIBRARIES(${PRO_LIBOASIDOC_NAME} BZip2 )

set_target_properties(${PRO_LIBOASIDOC_NAME} PROPERTIES VERSION ${MYLIB_VERSION_STRING} SOVERSION ${MYLIB_VERSION_STRING})


message(“INSTALL_LIB_TO_DIR:” ${LIB_TARGET_CURRENT} )
install(TARGETS ${PRO_LIBOASIDOC_NAME} LIBRARY DESTINATION ${LIB_TARGET_CURRENT})
message("End read google ${PRO_LIBOASIDOC_NAME} file source e header.")
