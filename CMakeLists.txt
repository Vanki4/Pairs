cmake_minimum_required(VERSION 3.20)

project(Pairs LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(SFML 3 REQUIRED COMPONENTS Graphics Window System)

add_executable(Pairs
    main.cpp
    game.cpp
    card.cpp
    gameFunc.cpp
)

target_link_libraries(Pairs PRIVATE
    SFML::Graphics
    SFML::Window
    SFML::System
)