cmake_minimum_required(VERSION 3.15)
project(app_project)

# add hello_lib
# experiment on adding libraries
include_directories(hello_lib/install/include)
link_directories(hello_lib/install/lib)

# add GLFW for window creation
include_directories(src/glfw-3.3.2.bin.MACOS/include/GLFW)
link_directories(src/glfw-3.3.2.bin.MACOS/lib-macos)

# add glew
include_directories(src/glew/include)
link_directories(src/glew/lib)

# stb - image loader
include_directories(stb-lib)

add_executable(main src/main.cpp)
# add the OpenGL framework
target_link_libraries(main "-framework OpenGL")
target_link_libraries(main glfw_c)
target_link_libraries(main gle)

add_executable(one src/chapter-1.cpp)
target_link_libraries(one "-framework OpenGL")
target_link_libraries(one glfw.3)
target_link_libraries(one GLEW)

add_executable(tri src/triangle/tri.cpp)
target_link_libraries(tri "-framework OpenGL")
target_link_libraries(tri glfw.3)
target_link_libraries(tri GLEW)

add_executable(blast src/blastoff.c)

add_executable(nc src/triangle.c)
target_link_libraries(nc ncurses)
find_library(glew GLEW src/glew/lib)
target_link_libraries(nc glew)

add_executable(two src/chapter-2.cpp)
target_link_libraries(two "-framework OpenGL")
target_link_libraries(two glfw.3)
target_link_libraries(two GLEW)

add_executable(tex src/textures.cpp)
target_link_libraries(tex "-framework OpenGL")
target_link_libraries(tex glfw.3)
target_link_libraries(tex GLEW)