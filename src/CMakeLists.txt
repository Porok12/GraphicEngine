add_subdirectory(math)
add_subdirectory(core)
add_executable(main main.cpp)

target_link_libraries(main math core)