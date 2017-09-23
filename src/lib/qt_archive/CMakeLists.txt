set(HAVE_BZIP2_SUPPORT ${BZIP2_FOUND})
if(BZIP2_FOUND AND BZIP2_NEED_PREFIX)
    set(NEED_BZ2_PREFIX 1)
endif()

set(HAVE_XZ_SUPPORT ${LIBLZMA_FOUND})

configure_file(config-compression.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config-compression.h)
add_definitions(-DQT_NO_CAST_FROM_ASCII)

if(BZIP2_FOUND)
    include_directories(${BZIP2_INCLUDE_DIR})
    set(karchive_OPTIONAL_SRCS ${karchive_OPTIONAL_SRCS} kbzip2filter.cpp)
    set(karchive_OPTIONAL_LIBS ${karchive_OPTIONAL_LIBS} ${BZIP2_LIBRARIES})
endif()

if(LIBLZMA_FOUND)
    include_directories(${LIBLZMA_INCLUDE_DIRS})
    set(karchive_OPTIONAL_SRCS ${karchive_OPTIONAL_SRCS} kxzfilter.cpp k7zip.cpp)
    set(karchive_OPTIONAL_LIBS ${karchive_OPTIONAL_LIBS} ${LIBLZMA_LIBRARIES})
endif()


set(karchive_SRCS
    karchive.cpp
    kar.cpp
    kcompressiondevice.cpp
    kfilterbase.cpp
    kfilterdev.cpp
    kgzipfilter.cpp
    klimitediodevice.cpp
    knonefilter.cpp
    ktar.cpp
    kzip.cpp
    krcc.cpp
)

add_library(qt_archive_api ${karchive_SRCS} ${karchive_OPTIONAL_SRCS})
generate_export_header(qt_archive_api BASE_NAME KArchive)
add_library(KF5::Archive ALIAS qt_archive_api)

target_include_directories(qt_archive_api
    INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF5}/KArchive>"
)

target_link_libraries(qt_archive_api
    PUBLIC
        Qt5::Core
    PRIVATE
        ${karchive_OPTIONAL_LIBS}
        ${ZLIB_LIBRARY}
)

set_target_properties(qt_archive_api PROPERTIES
    VERSION     ${KARCHIVE_VERSION_STRING}
    SOVERSION   ${KARCHIVE_SOVERSION}
    EXPORT_NAME "Archive"
)

ecm_generate_headers(KArchive_HEADERS
    HEADER_NAMES
    KArchive
    KArchiveEntry
    KArchiveFile
    KArchiveDirectory
    KAr
    KCompressionDevice
    KFilterBase
    KFilterDev
    KTar
    KZip
    KZipFileEntry

    REQUIRED_HEADERS KArchive_HEADERS
)

install(TARGETS qt_archive_api
        EXPORT qt_archive_apiTargets
        ${KF5_INSTALL_TARGETS_DEFAULT_ARGS})

if(LIBLZMA_FOUND)
    ecm_generate_headers(KArchive_HEADERS
        HEADER_NAMES
        K7Zip
        REQUIRED_HEADERS KArchive_HEADERS
    )
endif()

install(FILES
            ${CMAKE_CURRENT_BINARY_DIR}/karchive_export.h
            ${KArchive_HEADERS}
        DESTINATION "../lib"
        COMPONENT Devel)

# include(ECMGeneratePriFile)
# ecm_generate_pri_file(BASE_NAME KArchive LIB_NAME qt_archive_api DEPS "core" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF5}/KArchive)
# install(FILES ${PRI_FILENAME} DESTINATION ${ECM_MKSPECS_INSTALL_DIR})

