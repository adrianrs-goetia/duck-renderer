cmake_minimum_required(VERSION 3.26)
project(CDuckyC)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_FLAGS "-Wall -g -Debug")
set(APP_NAME cduckyc)

include_directories(
    thirdparty/raylib/include
    thirdparty/tinyobjloader
)

link_directories("${CMAKE_SOURCE_DIR}/thirdparty/raylib/lib/")
link_libraries(raylib m)

add_compile_definitions(APP_NAME="${APP_NAME}")

add_executable(${APP_NAME}
    src/main.c
)
