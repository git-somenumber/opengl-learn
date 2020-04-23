cmake_minimum_required(VERSION 3.15)
project(app_project)

# add hello_lib
# experiment on adding libraries
include_directories(hello_lib/install/include)
link_directories(hello_lib/install/lib)

# add GLFW for window creation
include_directories(src/glfw-3.3.2.bin.MACOS/include/GLFW)
link_directories(src/glfw-3.3.2.bin.MACOS/lib-macos)

include_directories(src/glm)

# add glew
include_directories(src/glew/include)
link_directories(src/glew/lib)

# stb - image loader
include_directories(stb-lib)

add_subdirectory(src)

add_executable(main src/main.cpp)
# add the OpenGL framework
target_link_libraries(main "-framework OpenGL")
target_link_libraries(main glfw_c)
target_link_libraries(main gle)
