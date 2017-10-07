   cmake_minimum_required(VERSION 3.1)
   # Determine the PATH of Project target install
   set(PWD "${CMAKE_CURRENT_SOURCE_DIR}")
   INCLUDE (${PWD}/../../DocumentRoot.cmake)
   # the Info.plist template to fill after cmake md Info.plist is ready on bundle dir
   set(CMAKE_MODULE_PATH "${PWD}/cmake")
   # Determine the operating system in detail
   INCLUDE (${PWD}/cmake/FindOS.cmake)
   project(OasiSpeaker CXX)
   # build console version && bundle mac on mac!!
   # Project information.
   set(PRO_MAC_DESC_NAME "Oasi Document Speaker")
   set(CURRENT_VERSION "1.4.0")
   
   _CURRENTDIR_()
   # copy licence to bundle  font also hook app
   set(DIRLICENCE_A "${PWD}/dest_bundle/")
   set(CMAKE_AUTOMOC ON)
   set(CMAKE_INCLUDE_CURRENT_DIR ON)
   

   
   set(CMAKE_CXX_STANDARD 14)
   
   # main app module to load... printsupport
   # find_package( Qt5::Qt5Core REQUIRED ) Qt5Network 
   # Qt5Widgets require Core!  find_package(Qt5Widgets)
   
   find_package(Qt5Core REQUIRED)
   get_target_property(QtCore_location Qt5::Core LOCATION)
   
   find_package( Qt5Widgets REQUIRED )
   find_package( Qt5Gui REQUIRED )
   find_package( Qt5Xml REQUIRED )
   find_package( Qt5Svg REQUIRED )
   # find_package( Qt5Network REQUIRED )

   set(QT5DIR ${QtCore_location})
   
   
   # Core Widgets Gui Xml TextToSpeech PrintSupport Network Xml Svg Pdfium
   # Qt5::TextToSpeech Qt5::Pdfium Qt5::Gui  
   # Qt5::Widgets Qt5::Network Qt5::PrintSupport Qt5::Xml Qt5::Svg
   # OPTIONAL PART CAN RUN WHITOUT THIS
    find_package( PopplerQt5 )
    find_package( Qt5Pdfium )
	find_package( Qt5TextToSpeech )
	find_package( Qt5PrintSupport )
   
   #find_package( qt_language_detect_api )
   #find_package( qt_oasidocuments_api )
   # CMAKE_FIND_ROOT_PATH_BOTH ${DIR_LIBTARGET}  
   find_library (QOASI NAMES qt_oasidocuments_api PATHS ${DIR_LIBTARGET} NO_DEFAULT_PATH)
   find_library (QCLD2 NAMES qt_language_detect_api PATHS ${DIR_LIBTARGET} NO_DEFAULT_PATH)
   
   set( EXTRA_LIBS ${EXTRA_LIBS} ${QOASI} )
   set( EXTRA_LIBS ${EXTRA_LIBS} ${QCLD2} )
   
   set(CMAKE_AUTOMOC ON)
   set(CMAKE_INCLUDE_CURRENT_DIR ON)
   
   # main app sources file need this dir...
   INCLUDE_DIRECTORIES(${PWD}/../lib/oasidoc/)
   INCLUDE_DIRECTORIES(${PWD}/../lib/oasidoc/rtf-qt)
   INCLUDE_DIRECTORIES(${PWD}/../lib/oasidoc/epub)
   INCLUDE_DIRECTORIES(${PWD}/../lib/oasidoc/zlib)
   INCLUDE_DIRECTORIES(${PWD}/../lib/oasidoc/ooo)
   INCLUDE_DIRECTORIES(${PWD}/../lib/qcld2/include_cld2)
   
    # put in source on script rcc to have image in console modus mac no bundle..
    # set(RESOURCE ${PWD}/oasispeech.qrc )
    # qt5_add_resources(RESOURCE_ADDED ${RESOURCE})
    #exec_program(./buildrcc.sh ${PWD} OUTPUT_VARIABLE SDOUTVALUE)
    # message("BUILD_RCC_SAY: XXXXXXXXXX${SDOUTVALUE}XXXXXXXXXXX ")
   
   # main app build init + resource file oasispeech.qrc as .cpp .
   file (GLOB SRC_FILES ${PWD}/*.cpp  )
   set(CMAKE_BUILD_TYPE Release)
   
   message("USE OF QT5 PATH -> XXXXXXXXXXX" ${QT5DIR} "XXXXXXXXXXX")
   
   # shared lib not qt5 module!
   IF (POPPLER_QT5_FOUND)
   add_definitions(-DPOPPLERQT5LOAD_OK)
   message("SHARED Library name PopplerQt5 Found Super.  XXXXXXXXXXX${POPPLER_QT5_INCLUDE_DIR}XXXXXXXXXXX ")
   include_directories( ${PopplerQt5_INCLUDE_DIRS} )
   ENDIF()
   
   # qt5 module optional if having we use.. 
    
    IF (Qt5Pdfium_FOUND)
    # do stuff
    add_definitions(-DPDFIUMISLOAD_OK)
    message("QT5 MODULE Library name Qt5Pdfium Found Super. XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX ")
    ELSE()
    # do other stuff
    message("Library name Qt5Pdfium NOT EXIT! WE SEARCH POPPLER_QT5 NOW...")
    message("Get Qt5Pdfium on: git clone --recursive https://github.com/paulovap/qtpdfium.git ")
    ENDIF()
	
    IF (Qt5PrintSupport_FOUND)
    message("QT5 MODULE Library name Qt5PrintSupport Found Super  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX ")
	add_definitions(-DQTPRINTSUPPORT_OK)
    ENDIF()
	
    IF (Qt5TextToSpeech_FOUND)
    # do stuff
    add_definitions(-DQT5SPEEHLOAD_OK)
    message("QT5 MODULE Library name Qt5TextToSpeech Found Super.  XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX ")
    ENDIF()
	

     
   # make a simple CONSOLE APP as mac or sipmple linux 
   if(SAYUNAME MATCHES "(NOTEXIST*)") 
   add_executable( ${PRO_UNIX_NAME} ${SRC_FILES} )
   qt5_use_modules(${PRO_UNIX_NAME} Core Widgets Gui Xml  )
   IF (Qt5Pdfium_FOUND)
   qt5_use_modules(${PRO_UNIX_NAME} Pdfium )
   ENDIF()
   IF (Qt5PrintSupport_FOUND)
   qt5_use_modules(${PRO_UNIX_NAME} PrintSupport )
   ENDIF()
   IF (Qt5TextToSpeech_FOUND)
   qt5_use_modules(${PRO_UNIX_NAME} TextToSpeech )
   ENDIF()
   IF (POPPLER_QT5_FOUND)
   # target_link_libraries( ${PRO_UNIX_NAME} ${POPPLER_QT5_LIBRARIES} )
   ENDIF()
   target_link_libraries( ${PRO_UNIX_NAME} ${EXTRA_LIBS} )
   endif()
   # end CONSOLE APP
   
   set(CMAKE_INSTALL_PREFIX ${CMAKE_INSTALL_PREFIX_0})
   
   message("1- RELINK SHARED LIB IF EXIST ${SIGNALAPPBUILD}  BUNDLE LIB PREPARE ")
   
   
   if (UNIX OR APPLE)
   	if (EXISTS ${SIGNALAPPBUILD})
      message("2- RELINK SHARED LIB IF EXIST ${SIGNALAPPBUILD}  BUNDLE LIB PREPARE ")
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
		message("FOR -> RELINK FILE ${LIBFULLEXIST} bundle ")
   		install_symlink( ${LIBFULLEXIST} ${LIBFULLEXIST} )
       ENDFOREACH(infileName)
       endif()
   endif()
   
   
   
   # ${CMAKE_INSTALL_PREFIX}
   # beginn BUNDLE BUILD PACKAGE APP 
   if(SAYUNAME MATCHES "(Darw*)")
	 message("BUNDLE APP START - XXXXX ${PWD} XXXXX ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}  XXXXXXXXXXX ")
	 set(MACICONLOCATION ${CMAKE_CURRENT_SOURCE_DIR}/images/ODTicon.icns)
     string(TIMESTAMP PROJECT_COPYRIGHT "© 1999-%Y P.Kopp All Rights Reserved." UTC)
     set(PROJECT_DESCRIPTION "${PRO_MACOSX_NAME}, A simple Editor to give Voice on Your Documents.")
	 set(MACOSX_BUNDLE_ICON_FILE "ODTicon.icns")
	 set(MACOSX_BUNDLE_INFO_STRING "${PRO_MACOSX_NAME}")
	 set(MACOSX_BUNDLE_GUI_IDENTIFIER "github.com/pehohlva/QOASIS")
	 set(MACOSX_BUNDLE_LONG_VERSION_STRING "${PROJECT_DESCRIPTION} Version ${CURRENT_VERSION}")
	 set(MACOSX_BUNDLE_BUNDLE_NAME ${PRO_MACOSX_NAME})
	 set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${CURRENT_VERSION})
	 set(MACOSX_BUNDLE_BUNDLE_VERSION ${CURRENT_VERSION})
	 set(MACOSX_BUNDLE_COPYRIGHT ${PROJECT_COPYRIGHT})
	 set(MACOSX_BUNDLE_EXECUTABLE_NAME ${PRO_MACOSX_NAME})
     add_executable(${PRO_MACOSX_NAME} MACOSX_BUNDLE ${SRC_FILES} ${MACICONLOCATION} )
	 set_target_properties(${PRO_MACOSX_NAME} PROPERTIES BUNDLE_EXTENSION app)
     qt5_use_modules(${PRO_MACOSX_NAME} Core Widgets Gui Xml  )
     IF (Qt5Pdfium_FOUND)
     qt5_use_modules(${PRO_MACOSX_NAME} Pdfium )
     ENDIF()
     IF (Qt5PrintSupport_FOUND)
     qt5_use_modules(${PRO_MACOSX_NAME} PrintSupport )
     ENDIF()
     IF (Qt5TextToSpeech_FOUND)
     qt5_use_modules(${PRO_MACOSX_NAME} TextToSpeech )
     ENDIF()
     IF (POPPLER_QT5_FOUND)
     # target_link_libraries( ${PRO_MACOSX_NAME} ${POPPLER_QT5_LIBRARIES} )
     ENDIF()
     target_link_libraries( ${PRO_MACOSX_NAME} ${EXTRA_LIBS} )
	 set_source_files_properties(${MACICONLOCATION} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
	 set_source_files_properties( "${CMAKE_CURRENT_SOURCE_DIR}/images/LICENSE.GPL2" PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
	 exec_program(pwd  OUTPUT_VARIABLE CACHEDIR)
	 set(DIRRESBUNDE "${CACHEDIR}/${PRO_MACOSX_NAME}.app/Contents/Resources")
	 set(EXECAPPINBUNDLE "${CACHEDIR}/${PRO_MACOSX_NAME}.app/Contents/MacOS/${PRO_MACOSX_NAME}")
	 file(MAKE_DIRECTORY ${DIRRESBUNDE})
	 file(COPY ${DIRLICENCE_A} DESTINATION ${DIRRESBUNDE})
	 
	 ###install(CODE MESSAGE(STATUS "SAMPLE INSTALL & COMPOSE BUNDLE COMPRESSED FROM MAC OSX" ) 
	   if(EXISTS ${EXECAPPINBUNDLE})
       # After make if exec app bundle ready finalize ... 
       execute_process(COMMAND macdeployqt ${PRO_MACOSX_NAME}.app -dmg)
       exec_program("open" ${CACHEDIR}  ARGS "./")
	   endif()
	 ###)
     message("BUNDLE APP END - XXXXXXXXXXXXXX ${DIRRESBUNDE} XXXXXXXXXXXXXXXXXXXXXXXXXXXXX ")
   endif()
   # end MAC OSX DARWIN  APP
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   

   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
