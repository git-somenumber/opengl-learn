
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../)

add_executable(one chapter-1.cpp)
target_link_libraries(one "-framework OpenGL")
target_link_libraries(one glfw.3)
target_link_libraries(one GLEW)

add_executable(tri ./triangle/tri.cpp)
target_link_libraries(tri "-framework OpenGL")
target_link_libraries(tri glfw.3)
target_link_libraries(tri GLEW)

add_executable(blast ./blastoff.c)

add_executable(nc ./triangle.c)
target_link_libraries(nc ncurses)
find_library(glew GLEW ./glew/lib)
target_link_libraries(nc glew)

add_executable(two ./chapter-2.cpp)
target_link_libraries(two "-framework OpenGL")
target_link_libraries(two glfw.3)
target_link_libraries(two GLEW)

add_executable(tex ./textures.cpp)
target_link_libraries(tex "-framework OpenGL")
target_link_libraries(tex glfw.3)
target_link_libraries(tex GLEW)

add_executable(depth ./depth/depth.cpp)
target_link_libraries(depth "-framework OpenGL")
target_link_libraries(depth glfw.3)
target_link_libraries(depth GLEW)

add_executable(multi ./depth/multiple_3d.cpp)
target_link_libraries(multi "-framework OpenGL")
target_link_libraries(multi glfw.3)
target_link_libraries(multi GLEW)