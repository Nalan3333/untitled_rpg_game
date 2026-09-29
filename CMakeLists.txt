cmake_minimum_required(VERSION 4.2)
project(untitled_rpg_game C)

set(CMAKE_C_STANDARD 17)

add_executable(untitled_rpg_game
        src/main.c
        src/entity.c
        src/location.c
)