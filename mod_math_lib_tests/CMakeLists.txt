cmake_minimum_required(VERSION 3.11 FATAL_ERROR)
project(mod_math_lib_tests CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(INCLUDE_DIR include)
set(SOURCE_DIR src)

set(sources main.cpp ${MOD_MATH_LIB_DIR}/include/mod_math_lib.h)

add_executable(mod_math_lib_tests ${sources} ${includes})

target_include_directories(mod_math_lib_tests PRIVATE ${MOD_MATH_LIB_DIR}/include)

target_link_libraries(mod_math_lib_tests PRIVATE mod_math_lib)

set_target_properties(mod_math_lib_tests PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED YES
        CXX_EXTENSIONS NO)
