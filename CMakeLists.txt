cmake_minimum_required(VERSION 3.24)
project(final C)

set(CMAKE_C_STANDARD 11)

add_executable(final main.c)
INCLUDE_DIRECTORIES( C:/mingw32/include )
LINK_DIRECTORIES( C:/mingw32/lib )

TARGET_LINK_LIBRARIES(final allegro allegro_font allegro_primitives
        allegro_ttf allegro_image allegro_acodec allegro_audio)
