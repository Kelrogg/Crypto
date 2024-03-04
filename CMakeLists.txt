cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(infosec_labs CXX)

set(MOD_MATH_LIB_DIR ${CMAKE_CURRENT_LIST_DIR}/mod_math_lib)

add_subdirectory(key_encryption)
add_subdirectory(mod_math_lib)
add_subdirectory(key_finder)

if ( BUILD_TESTS )
    add_subdirectory(mod_math_lib_tests)
endif()
