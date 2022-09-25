cmake_minimum_required(VERSION 3.18)
project(Pipeline LANGUAGES CXX)
add_executable(Pipeline)

set_property(TARGET Pipeline PROPERTY CXX_STANDARD 20)


target_sources(Pipeline
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include/niragne/pipeline.h>
    PRIVATE
        src/main.cpp
)

target_include_directories(Pipeline
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
    PRIVATE
        include/niragne
        src
)