add_subdirectory(IO)
add_subdirectory(utils)

add_executable(game main.cpp)
target_link_libraries(game formattedio)
