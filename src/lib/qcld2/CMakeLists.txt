cmake_minimum_required(VERSION 3.6)
project(QTCLD2 C CXX)
set(PRO_LIBCLD2_NAME "QTCLD2")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

message("Init read google cld2 file source e header.")


find_package( Qt5Core REQUIRED )

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

INCLUDE_DIRECTORIES({CMAKE_CURRENT_SOURCE_DIR}/)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/public)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/internal)

set(CMAKE_BUILD_TYPE Release)

list(APPEND QTCLD2_SOURCES
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/scoreonescriptspan.cc" 
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/cldutil.cc"  
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/cldutil_shared.cc"  
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/compact_lang_det.cc"   
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/compact_lang_det_hint_code.cc" 
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/compact_lang_det_impl.cc"   
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/debug.cc" 
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/fixunicodevalue.cc"  
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/generated_entities.cc"   
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/generated_language.cc"  
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/generated_ulscript.cc"  
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/getonescriptspan.cc" 
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/lang_script.cc" 
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/offsetmap.cc"  
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/tote.cc" 
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/utf8statetable.cc"  
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/generated_distinct_bi_0.cc"  
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/cld_generated_cjk_uni_prop_80.cc" 
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/cld_generated_cjk_delta_bi_4.cc" 
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/cld_generated_score_quad_octa_2.cc"
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/cld2_generated_quadchrome_2.cc" 
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/cld2_generated_deltaoctachrome.cc" 
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/cld2_generated_distinctoctachrome.cc" 
    "${CMAKE_CURRENT_SOURCE_DIR}/internal/cld2_generated_cjk_compatible.cc"
    "${CMAKE_CURRENT_LIST_DIR}/datalanguageprovider.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/qtrlocale.cpp"
)



add_library(${PRO_LIBCLD2_NAME} STATIC ${QTCLD2_SOURCES})
# qt5_use_modules(${PRO_LIBCLD2_NAME} Qt5Core )
target_link_libraries(${PRO_LIBCLD2_NAME} Qt5::Core)




message("End read google cld2 file source e header.")
