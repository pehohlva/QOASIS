cmake_minimum_required(VERSION 3.6)
project(QTCLD2 C CXX)
set(PRO_LIBCLD2_NAME "qt_language_detect_api")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
# qmake style to copy file from pri qt5 only replace ${PWD}
set(PWD "${CMAKE_CURRENT_SOURCE_DIR}") 
message("Init read google ${PRO_LIBCLD2_NAME} file source e header.")


find_package( Qt5Core REQUIRED )

set(CMAKE_AUTOMOC OFF)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

INCLUDE_DIRECTORIES({PWD}/)
INCLUDE_DIRECTORIES(${PWD}/source_cld2)
INCLUDE_DIRECTORIES(${PWD}/include_cld2)

set(CMAKE_BUILD_TYPE Release)


list(APPEND QTCLD2_SOURCES
           ${PWD}/source_cld2/cld2_generated_cjk_compatible.cc 
           ${PWD}/source_cld2/cld2_generated_deltaoctachrome.cc 
           ${PWD}/source_cld2/cld2_generated_distinctoctachrome.cc 
           ${PWD}/source_cld2/cld2_generated_quadchrome_2.cc 
           ${PWD}/source_cld2/cld_generated_cjk_delta_bi_4.cc 
           ${PWD}/source_cld2/cld_generated_cjk_uni_prop_80.cc 
           ${PWD}/source_cld2/cld_generated_score_quad_octa_2.cc 
           ${PWD}/source_cld2/cldutil.cc 
           ${PWD}/source_cld2/cldutil_shared.cc 
           ${PWD}/source_cld2/compact_lang_det.cc 
           ${PWD}/source_cld2/compact_lang_det_hint_code.cc 
           ${PWD}/source_cld2/compact_lang_det_impl.cc 
           ${PWD}/source_cld2/datalanguageprovider.cpp 
           ${PWD}/source_cld2/debug.cc 
           ${PWD}/source_cld2/fixunicodevalue.cc 
           ${PWD}/source_cld2/generated_distinct_bi_0.cc 
           ${PWD}/source_cld2/generated_entities.cc 
           ${PWD}/source_cld2/generated_language.cc 
           ${PWD}/source_cld2/generated_ulscript.cc 
           ${PWD}/source_cld2/getonescriptspan.cc 
           ${PWD}/source_cld2/lang_script.cc 
           ${PWD}/source_cld2/offsetmap.cc 
           ${PWD}/source_cld2/qtrlocale.cpp 
           ${PWD}/source_cld2/scoreonescriptspan.cc 
           ${PWD}/source_cld2/tote.cc 
           ${PWD}/source_cld2/utf8statetable.cc
)
set(QTCLD2_HEADERS
           ${PWD}/include_cld2/cldutil.h 
		   ${PWD}/include_cld2/stringpiece.h
		   ${PWD}/include_cld2/langspan.h
		   ${PWD}/include_cld2/port.h
		   ${PWD}/include_cld2/utf8repl_lettermarklower.h
		   ${PWD}/include_cld2/utf8scannot_lettermarkspecial.h
		   ${PWD}/include_cld2/utf8prop_lettermarkscriptnum.h
		   ${PWD}/include_cld2/utf8acceptinterchange.h
           ${PWD}/include_cld2/cldutil_shared.h 
		   ${PWD}/include_cld2/cld2tablesummary.h
           ${PWD}/include_cld2/compact_lang_det.h 
           ${PWD}/include_cld2/compact_lang_det_hint_code.h 
           ${PWD}/include_cld2/compact_lang_det_impl.h 
           ${PWD}/include_cld2/datalanguageprovider.h 
           ${PWD}/include_cld2/debug.h 
           ${PWD}/include_cld2/encodings.h 
           ${PWD}/include_cld2/fixunicodevalue.h 
           ${PWD}/include_cld2/generated_language.h 
           ${PWD}/include_cld2/generated_ulscript.h 
           ${PWD}/include_cld2/getonescriptspan.h 
           ${PWD}/include_cld2/integral_types.h 
           ${PWD}/include_cld2/lang_script.h 
           ${PWD}/include_cld2/offsetmap.h 
           ${PWD}/include_cld2/qtrlocale.h 
           ${PWD}/include_cld2/scoreonescriptspan.h 
           ${PWD}/include_cld2/tote.h 
           ${PWD}/include_cld2/utf8statetable.h
)

add_library(${PRO_LIBCLD2_NAME} SHARED ${QTCLD2_SOURCES})
# qt5_use_modules(${PRO_LIBCLD2_NAME} Qt5Core )
target_link_libraries(${PRO_LIBCLD2_NAME} Qt5::Core)


message("End read google ${PRO_LIBCLD2_NAME} file source e header.")
