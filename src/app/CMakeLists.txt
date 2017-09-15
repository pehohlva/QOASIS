   cmake_minimum_required(VERSION 3.7)
   # the Info.plist template to fill after cmake md Info.plist is ready on bundle dir
   set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
   project(OasiSpeaker CXX)
   set(PRO_UNIX_NAME "oasispeak")
   set(PRO_MACOSX_NAME "OasiSpeaker")
   # Project information.
   set(PRO_MAC_DESC_NAME "Oasi Document Speaker")
   set(CURRENT_VERSION "1.4.0")
   set(PWD "${CMAKE_CURRENT_SOURCE_DIR}")
   
   
   set(CMAKE_AUTOMOC ON)
   set(CMAKE_INCLUDE_CURRENT_DIR ON)
   
   # Project Bundle to info plist xml file information.
   set(PROJECT_COMPANY_NAME "OasiSpeaker Company")
   string(TIMESTAMP PROJECT_COPYRIGHT "© 1999-%Y P.Kopp All Rights Reserved." UTC)
   set(PROJECT_DESCRIPTION "A simple Editor to give Voice on Your Documents.")
   set(PROJECT_URL "https://www.qt.io/")
   # the property added to Info.plist
   set(MACOSX_BUNDLE_ICON_FILE "macicon.icns")

   # Set the OS X Bundle specific CMake variables which will be used to populate the plist for
   # the application bundle
   set(MACOSX_BUNDLE_INFO_STRING "${PRO_MACOSX_NAME}")
   set(MACOSX_BUNDLE_GUI_IDENTIFIER "com.qt.io")
   set(MACOSX_BUNDLE_LONG_VERSION_STRING "${PRO_MAC_DESC_NAME} Version ${CURRENT_VERSION}")
   set(MACOSX_BUNDLE_BUNDLE_NAME ${PRO_MACOSX_NAME})
   set(MACOSX_BUNDLE_SHORT_VERSION_STRING ${CURRENT_VERSION})
   set(MACOSX_BUNDLE_BUNDLE_VERSION ${CURRENT_VERSION})
   set(MACOSX_BUNDLE_COPYRIGHT ${PROJECT_COPYRIGHT})
   set(MACOSX_BUNDLE_EXECUTABLE_NAME ${PRO_MACOSX_NAME})
   # And this part tells CMake where to find and install the file itself
   set(MAC_APP_ICON ${CMAKE_CURRENT_SOURCE_DIR}/images/ODTicon.icns)
   set_source_files_properties(${MAC_APP_ICON} PROPERTIES MACOSX_PACKAGE_LOCATION "Resources")
   
   set(CMAKE_CXX_STANDARD 14)
   
   # main app module to load... printsupport
   # find_package( Qt5::Qt5Core REQUIRED )
   # Qt5Widgets require Core!  find_package(Qt5Widgets)
   
   find_package(Qt5Core REQUIRED)
   get_target_property(QtCore_location Qt5::Core LOCATION)
   
   find_package( Qt5Widgets REQUIRED )
   find_package( Qt5Gui REQUIRED )
   find_package( Qt5Xml REQUIRED )
   find_package( Qt5Svg REQUIRED )
   find_package( Qt5Network REQUIRED )

   set(QT5DIR ${QtCore_location})
   
   
   # Core Widgets Gui Xml TextToSpeech PrintSupport Network Xml Svg Pdfium
   # Qt5::TextToSpeech Qt5::Pdfium Qt5::Gui  
   # Qt5::Widgets Qt5::Network Qt5::PrintSupport Qt5::Xml Qt5::Svg
   # OPTIONAL PART CAN RUN WHITOUT THIS
    find_package( PopplerQt5 )
    find_package( Qt5Pdfium )
	find_package( Qt5TextToSpeech )
	find_package( Qt5PrintSupport )
   


    


   
   find_library (QOASI NAMES qt_oasidocuments_api PATHS ../lib NO_DEFAULT_PATH)
   find_library (QCLD2 NAMES qt_language_detect_api PATHS ../lib NO_DEFAULT_PATH)
   
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
    exec_program(./buildrcc.sh ${PWD} OUTPUT_VARIABLE SDOUTVALUE)
    message("BUILD_RCC_SAY: XXXXXXXXXX${SDOUTVALUE}XXXXXXXXXXX ")
   
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
	
	
   
   
   add_executable( ${PRO_UNIX_NAME} ${SRC_FILES} )
   qt5_use_modules(${PRO_UNIX_NAME} Core Widgets Gui Xml Network Xml Svg  )
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
   target_link_libraries( ${PRO_UNIX_NAME} ${POPPLER_QT5_LIBRARIES} )
   ENDIF()
   target_link_libraries( ${PRO_UNIX_NAME} ${EXTRA_LIBS} )
   
   
# qt5_use_modules(${PRO_UNIX_NAME} PrintSupport  )
# target_link_libraries(${PRO_UNIX_NAME} Qt5::Pdfium)
# qt5_use_modules(${PRO_UNIX_NAME} Qt5TextToSpeech  )
   
   
   
   
   
   
   
   
   
   
   
   
   
   

   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
