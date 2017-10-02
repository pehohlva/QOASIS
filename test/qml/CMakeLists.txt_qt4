cmake_minimum_required(VERSION 3.9)
set(PWD "${CMAKE_CURRENT_SOURCE_DIR}")
# INCLUDE (${PWD}/../../DocumentRoot.cmake)

project(hook CXX)

#qt4 force set(QT_ROOT /opt/local/libexec/qt4) 
# set(ENV(CMAKE_PREFIX_PATH) ${QT_ROOT} )
find_package (Qt4 COMPONENTS QtCore QtGui QtNetwork  QtSvg QtDeclarative QtXml QtOpengl QtHelp QtUiTools QtSql  QtScriptTools QtScript QtMultimedia )
INCLUDE(${QT_USE_FILE})

set(CMAKE_INCLUDE_CURRENT_DIR ON)

#  also subpath ${PWD}/page/*.cpp
file (GLOB HEAD_FILES ${PWD}/*.h )
file (GLOB SRCBASE_FILES ${PWD}/*.cpp ${PWD}/*.qrc )
set(Source_Cpp ${SRCBASE_FILES})


set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


set(CMAKE_CXX_STANDARD 11)



add_executable(${PROJECT_NAME} ${Source_Cpp} )
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
TARGET_LINK_LIBRARIES(${PROJECT_NAME} ${QT_LIBRARIES})


message("End line from cmakelist.txt ................ :-)"  ${PROJECT_NAME} )
