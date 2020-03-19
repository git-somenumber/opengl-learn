

add_executable(main main.c)

add_library(test STATIC hello.c)
target_link_libraries(main test)
target_include_directories(main PUBLIC "${PROJECT_BINARY_DIR}" "${PROJECT_SOURCE_DIR}")
install(TARGETS test DESTINATION lib)
install(FILES src/test.h DESTINATION include)
install(TARGETS main DESTINATION bin)
