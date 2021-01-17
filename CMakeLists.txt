cmake_minimum_required(VERSION 3.10)

add_subdirectory(src)

include_directories(src)
add_executable(s1_01 s1_01.cpp)
target_link_libraries(s1_01 cryptopals132)

add_executable(s1_02 s1_02.cpp)
target_link_libraries(s1_02 cryptopals132)

add_executable(s1_03 s1_03.cpp)
target_link_libraries(s1_03 cryptopals132)

add_executable(s1_04 s1_04.cpp)
target_link_libraries(s1_04 cryptopals132)

add_executable(s1_05 s1_05.cpp)
target_link_libraries(s1_05 cryptopals132)

add_executable(s1_06 s1_06.cpp)
target_link_libraries(s1_06 cryptopals132)
