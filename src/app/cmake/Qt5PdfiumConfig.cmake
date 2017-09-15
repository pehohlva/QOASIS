
if (CMAKE_VERSION VERSION_LESS 2.8.3)
    message(FATAL_ERROR "Qt 5 requires at least CMake version 2.8.3")
endif()

get_filename_component(_qt5Pdfium_install_prefix "${CMAKE_CURRENT_LIST_DIR}/../../../" ABSOLUTE)

# For backwards compatibility only. Use Qt5Pdfium_VERSION instead.
set(Qt5Pdfium_VERSION_STRING 5.5.0)

set(Qt5Pdfium_LIBRARIES Qt5::Pdfium)

macro(_qt5_Pdfium_check_file_exists file)
    if(NOT EXISTS "${file}" )
        message(FATAL_ERROR "The imported target \"Qt5::Pdfium\" references the file
   \"${file}\"
but this file does not exist.  Possible reasons include:
* The file was deleted, renamed, or moved to another location.
* An install or uninstall procedure did not complete successfully.
* The installation package was faulty and contained
   \"${CMAKE_CURRENT_LIST_FILE}\"
but not all the files it references.
")
    endif()
endmacro()

macro(_populate_Pdfium_target_properties Configuration LIB_LOCATION IMPLIB_LOCATION)
    set_property(TARGET Qt5::Pdfium APPEND PROPERTY IMPORTED_CONFIGURATIONS ${Configuration})

    set(imported_location "${_qt5Pdfium_install_prefix}/lib/${LIB_LOCATION}")
    _qt5_Pdfium_check_file_exists(${imported_location})
    set_target_properties(Qt5::Pdfium PROPERTIES
        "INTERFACE_LINK_LIBRARIES" "${_Qt5Pdfium_LIB_DEPENDENCIES}"
        "IMPORTED_LOCATION_${Configuration}" ${imported_location}
        # For backward compatibility with CMake < 2.8.12
        "IMPORTED_LINK_INTERFACE_LIBRARIES_${Configuration}" "${_Qt5Pdfium_LIB_DEPENDENCIES}"
    )

endmacro()

if (NOT TARGET Qt5::Pdfium)

    set(_Qt5Pdfium_OWN_INCLUDE_DIRS
      "${_qt5Pdfium_install_prefix}/lib/QtPdfium.framework"
      "${_qt5Pdfium_install_prefix}/lib/QtPdfium.framework/Headers"
    )
    set(Qt5Pdfium_PRIVATE_INCLUDE_DIRS "")

    foreach(_dir ${_Qt5Pdfium_OWN_INCLUDE_DIRS})
        _qt5_Pdfium_check_file_exists(${_dir})
    endforeach()


    set(Qt5Pdfium_INCLUDE_DIRS ${_Qt5Pdfium_OWN_INCLUDE_DIRS})

    set(Qt5Pdfium_DEFINITIONS -DQT_PDFIUM_LIB)
    set(Qt5Pdfium_COMPILE_DEFINITIONS QT_PDFIUM_LIB)
    set(_Qt5Pdfium_MODULE_DEPENDENCIES "Gui;Core")


    set(Qt5Pdfium_OWN_PRIVATE_INCLUDE_DIRS ${Qt5Pdfium_PRIVATE_INCLUDE_DIRS})

    set(_Qt5Pdfium_FIND_DEPENDENCIES_REQUIRED)
    if (Qt5Pdfium_FIND_REQUIRED)
        set(_Qt5Pdfium_FIND_DEPENDENCIES_REQUIRED REQUIRED)
    endif()
    set(_Qt5Pdfium_FIND_DEPENDENCIES_QUIET)
    if (Qt5Pdfium_FIND_QUIETLY)
        set(_Qt5Pdfium_DEPENDENCIES_FIND_QUIET QUIET)
    endif()
    set(_Qt5Pdfium_FIND_VERSION_EXACT)
    if (Qt5Pdfium_FIND_VERSION_EXACT)
        set(_Qt5Pdfium_FIND_VERSION_EXACT EXACT)
    endif()

    set(Qt5Pdfium_EXECUTABLE_COMPILE_FLAGS "")

    foreach(_module_dep ${_Qt5Pdfium_MODULE_DEPENDENCIES})
        if (NOT Qt5${_module_dep}_FOUND)
            find_package(Qt5${_module_dep}
                5.5.0 ${_Qt5Pdfium_FIND_VERSION_EXACT}
                ${_Qt5Pdfium_DEPENDENCIES_FIND_QUIET}
                ${_Qt5Pdfium_FIND_DEPENDENCIES_REQUIRED}
                PATHS "${CMAKE_CURRENT_LIST_DIR}/.." NO_DEFAULT_PATH
            )
        endif()

        if (NOT Qt5${_module_dep}_FOUND)
            set(Qt5Pdfium_FOUND False)
            return()
        endif()

        list(APPEND Qt5Pdfium_INCLUDE_DIRS "${Qt5${_module_dep}_INCLUDE_DIRS}")
        list(APPEND Qt5Pdfium_PRIVATE_INCLUDE_DIRS "${Qt5${_module_dep}_PRIVATE_INCLUDE_DIRS}")
        list(APPEND Qt5Pdfium_DEFINITIONS ${Qt5${_module_dep}_DEFINITIONS})
        list(APPEND Qt5Pdfium_COMPILE_DEFINITIONS ${Qt5${_module_dep}_COMPILE_DEFINITIONS})
        list(APPEND Qt5Pdfium_EXECUTABLE_COMPILE_FLAGS ${Qt5${_module_dep}_EXECUTABLE_COMPILE_FLAGS})
    endforeach()
    list(REMOVE_DUPLICATES Qt5Pdfium_INCLUDE_DIRS)
    list(REMOVE_DUPLICATES Qt5Pdfium_PRIVATE_INCLUDE_DIRS)
    list(REMOVE_DUPLICATES Qt5Pdfium_DEFINITIONS)
    list(REMOVE_DUPLICATES Qt5Pdfium_COMPILE_DEFINITIONS)
    list(REMOVE_DUPLICATES Qt5Pdfium_EXECUTABLE_COMPILE_FLAGS)

    set(_Qt5Pdfium_LIB_DEPENDENCIES "Qt5::Gui;Qt5::Core")


    add_library(Qt5::Pdfium SHARED IMPORTED)
    set_property(TARGET Qt5::Pdfium PROPERTY FRAMEWORK 1)

    set_property(TARGET Qt5::Pdfium PROPERTY
      INTERFACE_INCLUDE_DIRECTORIES ${_Qt5Pdfium_OWN_INCLUDE_DIRS})
    set_property(TARGET Qt5::Pdfium PROPERTY
      INTERFACE_COMPILE_DEFINITIONS QT_PDFIUM_LIB)

    set(_Qt5Pdfium_PRIVATE_DIRS_EXIST TRUE)
    foreach (_Qt5Pdfium_PRIVATE_DIR ${Qt5Pdfium_OWN_PRIVATE_INCLUDE_DIRS})
        if (NOT EXISTS ${_Qt5Pdfium_PRIVATE_DIR})
            set(_Qt5Pdfium_PRIVATE_DIRS_EXIST FALSE)
        endif()
    endforeach()

    if (_Qt5Pdfium_PRIVATE_DIRS_EXIST
        AND NOT CMAKE_VERSION VERSION_LESS 3.0.0 )
        add_library(Qt5::PdfiumPrivate INTERFACE IMPORTED)
        set_property(TARGET Qt5::PdfiumPrivate PROPERTY
            INTERFACE_INCLUDE_DIRECTORIES ${Qt5Pdfium_OWN_PRIVATE_INCLUDE_DIRS}
        )
        set(_Qt5Pdfium_PRIVATEDEPS)
        foreach(dep ${_Qt5Pdfium_LIB_DEPENDENCIES})
            if (TARGET ${dep}Private)
                list(APPEND _Qt5Pdfium_PRIVATEDEPS ${dep}Private)
            endif()
        endforeach()
        set_property(TARGET Qt5::PdfiumPrivate PROPERTY
            INTERFACE_LINK_LIBRARIES Qt5::Pdfium ${_Qt5Pdfium_PRIVATEDEPS}
        )
    endif()

    _populate_Pdfium_target_properties(RELEASE "QtPdfium.framework/QtPdfium" "" )



    _populate_Pdfium_target_properties(DEBUG "QtPdfium.framework/QtPdfium" "" )



    file(GLOB pluginTargets "${CMAKE_CURRENT_LIST_DIR}/Qt5Pdfium_*Plugin.cmake")

    macro(_populate_Pdfium_plugin_properties Plugin Configuration PLUGIN_LOCATION)
        set_property(TARGET Qt5::${Plugin} APPEND PROPERTY IMPORTED_CONFIGURATIONS ${Configuration})

        set(imported_location "${_qt5Pdfium_install_prefix}/plugins/${PLUGIN_LOCATION}")
        _qt5_Pdfium_check_file_exists(${imported_location})
        set_target_properties(Qt5::${Plugin} PROPERTIES
            "IMPORTED_LOCATION_${Configuration}" ${imported_location}
        )
    endmacro()

    if (pluginTargets)
        foreach(pluginTarget ${pluginTargets})
            include(${pluginTarget})
        endforeach()
    endif()




_qt5_Pdfium_check_file_exists("${CMAKE_CURRENT_LIST_DIR}/Qt5PdfiumConfigVersion.cmake")

endif()
