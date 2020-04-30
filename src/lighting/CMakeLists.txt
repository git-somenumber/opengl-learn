
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../../)

add_executable(basic basic.cpp)
target_link_libraries(basic "-framework OpenGL")
target_link_libraries(basic glfw.3)
target_link_libraries(basic GLEW)

file(COPY light DESTINATION CMAKE_RUNTIME_OUTPUT_DIRECTORY/shaders)
