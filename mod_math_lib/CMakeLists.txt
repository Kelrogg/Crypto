cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(mod_math_lib CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(INCLUDE_DIR include)
set(SOURCE_DIR src)

set(includes
        ${INCLUDE_DIR}/mod_math_lib.h)

set(sources
        ${SOURCE_DIR}/mod_math_lib.cpp)

add_library(mod_math_lib ${sources} ${includes})

target_include_directories(mod_math_lib PRIVATE ${INCLUDE_DIR})

set_target_properties(mod_math_lib PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO)
