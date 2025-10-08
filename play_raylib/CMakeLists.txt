cmake_minimum_required(VERSION 3.16)
project(glb_loader C)
set(CMAKE_C_STANDARD 99)
set(RAYLIB_PATH "/opt/homebrew/")

include_directories(${RAYLIB_PATH}/include)


link_directories(${RAYLIB_PATH}/lib)
add_executable(${PROJECT_NAME} glb_loader.c)

target_link_libraries(${PROJECT_NAME}
    ${RAYLIB_PATH}/lib/libraylib.a
    "-framework Cocoa"
    "-framework OpenGL"
    "-framework IOKit"
    "-framework CoreVideo"
)
