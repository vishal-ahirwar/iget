
#Auto Genrated CMake file by aura CLI
#Copyright 2023 Vishal Ahirwar. #replace with your copyright notice.
cmake_minimum_required(VERSION 3.6...3.31)
project(get VERSION 1.0.0 LANGUAGES CXX)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(BUILD_SHARED_LIBS OFF)
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -funroll-loops")
set(COMPANY "Vishal Ahirwar")
string(TIMESTAMP CURRENT_YEAR "%Y")
set(COPYRIGHT "Copyright(c) ${CURRENT_YEAR} ${COMPANY}.")
include_directories(src ${CMAKE_BINARY_DIR})
configure_file(getconfig.h.in getconfig.h)
#@find Warning: Do not remove this line
add_subdirectory(external/cpr)
add_subdirectory(external/fmt)
file(GLOB SOURCES "src/*.cpp" "src/*.hpp" "src/*.hxx" "src/*.h" "src/*.cc" "src/*.cxx")
add_executable(${PROJECT_NAME} ${SOURCES})
install(TARGETS ${PROJECT_NAME} DESTINATION bin)
#@link Warning: Do not remove this line
target_link_libraries(${PROJECT_NAME} cpr::cpr fmt::fmt)