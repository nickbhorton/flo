
cmake_minimum_required(VERSION 3.15...4.0)
project(flo
    VERSION 0.1
    DESCRIPTION "flo game engine"
    LANGUAGES CXX
)

add_subdirectory(sandbox)

set(FLO_SOURCE_DIR src)

add_library(flo STATIC)
target_sources(flo PRIVATE
    ${FLO_SOURCE_DIR}/app.h
    ${FLO_SOURCE_DIR}/app.cpp
    ${FLO_SOURCE_DIR}/log/log.h
)
target_include_directories(flo PUBLIC ${FLO_SOURCE_DIR})
target_compile_options(flo PRIVATE -Wall -Werror)
target_compile_options(flo PUBLIC -std=c++20)

