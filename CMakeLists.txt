cmake_minimum_required(VERSION 3.8)
project(Cat_following_beam VERSION 0.1.0 LANGUAGES CXX)

file(GLOB src "src/*")
add_executable(${PROJECT_NAME} main.cpp ${src})

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR ${CMAKE_SOURCE_DIR}/libs/SFML/lib/cmake/SFML)

include_directories(${CMAKE_SOURCE_DIR}/libs/SFML/include)

target_link_libraries(${PROJECT_NAME} sfml-graphics)
find_package(SFML 2.6 REQUIRED graphics system audio network window)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)