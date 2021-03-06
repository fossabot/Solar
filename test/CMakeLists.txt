cmake_minimum_required(VERSION 3.8)
project(Solar)

set(CMAKE_CXX_STANDARD 14)

set(NAME SolarTest)

if (CMAKE_BUILD_TYPE MATCHES Debug)
  set(NAME ${NAME}D)
endif()

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/..)

set(SRCPATH ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCPATH ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(include)
include_directories(../include)

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Ofast")

if (CMAKE_BUILD_TYPE MATCHES Debug)
  set(NAME ${NAME}D)
  add_definitions(-DDEBUG=1)
endif()

set(SOURCE_FILES
        ${INCPATH}/BenchmarkResult.hpp
        ${INCPATH}/Direction.hpp
        ${INCPATH}/MemoryInfo.hpp
        ${INCPATH}/Movement.hpp
        ${INCPATH}/Position.hpp
        ${INCPATH}/TestComponent.hpp
        ${INCPATH}/TestSystem.hpp
        ${INCPATH}/TimeInfo.hpp
        ${SRCPATH}/BenchmarkResult.cpp
        ${SRCPATH}/Direction.cpp
        ${SRCPATH}/MemoryInfo.cpp
        ${SRCPATH}/Movement.cpp
        ${SRCPATH}/Position.cpp
        ${SRCPATH}/TestComponent.cpp
        ${SRCPATH}/TestSystem.cpp
        ${SRCPATH}/TimeInfo.cpp
        ${SRCPATH}/main.cpp)

add_executable(${NAME} ${SOURCE_FILES})
target_link_libraries(${NAME} Solar)