cmake_minimum_required(VERSION 3.8)
project(simple-game-2 VERSION 0.1.0 LANGUAGES CXX)

# IF(WIN32)
# SET(GUI_TYPE WIN32)
# ENDIF(WIN32)
# # Set some Apple MacOS Specific settings
# IF (APPLE)
# SET(GUI_TYPE MACOSX_BUNDLE)
# ENDIF (APPLE)

file(GLOB src "src/*")
add_executable(${PROJECT_NAME} ${GUI_TYPE} main.cpp ${src})

# IF(WIN32)
# target_compile_definitions(${PROJECT_NAME} PRIVATE ISWIN32=1)
# ENDIF(WIN32)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR ${CMAKE_SOURCE_DIR}/libs/SFML/lib/cmake/SFML)

include_directories(${CMAKE_SOURCE_DIR}/libs/SFML/include)

target_link_libraries(${PROJECT_NAME} sfml-graphics)
find_package(SFML 2.6 REQUIRED graphics system audio network window)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)