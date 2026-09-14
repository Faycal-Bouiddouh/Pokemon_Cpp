cmake_minimum_required(VERSION 3.21)
project(Pokemon)

set(CMAKE_CXX_STANDARD 17)

find_package(SFML 3 COMPONENTS Graphics Window System Audio REQUIRED)

file(GLOB SOURCES "Src/*.cpp")
add_executable(Pokemon ${SOURCES})

# 3. On indique que les fichiers d'en-tête (.hpp) sont dans le dossier Include
target_include_directories(Pokemon PRIVATE Include)

# 4. On lie la SFML à ton jeu (syntaxe moderne SFML::)
target_link_libraries(Pokemon PRIVATE 
    SFML::Graphics 
    SFML::Window 
    SFML::System 
    SFML::Audio
)