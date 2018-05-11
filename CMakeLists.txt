cmake_minimum_required(VERSION 3.8)
project(Solar)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(test)

set(NAME Solar)

set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})

set(SRCPATH ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCPATH ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(include)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Ofast")

if (CMAKE_BUILD_TYPE MATCHES Debug)
    set(NAME ${NAME}D)
    add_definitions(-DDEBUG=1)
endif()

set(SOURCE_FILES
        ${INCPATH}/AEntityScript.hpp
        ${INCPATH}/AWorldScript.hpp
        ${INCPATH}/ASceneScript.hpp
        ${INCPATH}/Component.hpp
        ${INCPATH}/Core.hpp
        ${INCPATH}/Entity.hpp
        ${INCPATH}/Indexer.hpp
        ${INCPATH}/InnerCore.hpp
        ${INCPATH}/Scene.hpp
        ${INCPATH}/System.hpp
        ${INCPATH}/SystemList.hpp
        ${INCPATH}/TimeIdx.hpp
        ${INCPATH}/Vector.hpp
        ${INCPATH}/World.hpp
        ${SRCPATH}/AEntityScript.cpp
        ${SRCPATH}/AWorldScript.cpp
        ${SRCPATH}/ASceneScript.cpp
        ${SRCPATH}/Core.cpp
        ${SRCPATH}/Entity.cpp
        ${SRCPATH}/Indexer.cpp
        ${SRCPATH}/InnerCore.cpp
        ${SRCPATH}/Scene.cpp
        ${SRCPATH}/System.cpp
        ${SRCPATH}/SystemList.cpp
        ${SRCPATH}/World.cpp)

add_library(${NAME} SHARED ${SOURCE_FILES})