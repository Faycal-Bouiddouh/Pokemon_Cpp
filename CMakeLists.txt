cmake_minimum_required(VERSION 3.21)
project(Pokemon)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

file(GLOB SOURCES CONFIGURE_DEPENDS "Src/*.cpp")
add_executable(Pokemon ${SOURCES}
    Include/PokemonApplication.hpp)

target_include_directories(Pokemon PRIVATE Include)
target_link_libraries(Pokemon PRIVATE SFML::Graphics SFML::Window SFML::System)
