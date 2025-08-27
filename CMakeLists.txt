
# Optionally set your Qt6 install path here if CMake cannot find it automatically:

cmake_minimum_required(VERSION 3.16)
project(hamster VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if ((MSVC))
	set(CMAKE_PREFIX_PATH "C:/Qt/6.9.2/msvc2022_64/")
endif()

find_package(Qt6 COMPONENTS Core Gui Widgets Multimedia REQUIRED)

add_executable(hamster
	src/main.cpp
	src/GameWidget.cpp
	src/Hamster.cpp
	src/Maze.cpp
)

target_include_directories(hamster PRIVATE include)

if ((MSVC))
	target_compile_options(hamster PUBLIC /permissive- /Zc:__cplusplus)
endif()

target_link_libraries(hamster Qt::Core Qt6::Gui Qt6::Widgets Qt6::Multimedia)
