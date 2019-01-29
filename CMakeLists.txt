cmake_minimum_required(VERSION 3.13)
project(aquarium)

set(CMAKE_CXX_STANDARD 17)

add_executable(aquarium main.cpp)

add_subdirectory(src)

target_link_libraries(aquarium Creature)
target_link_libraries(aquarium Field)
target_link_libraries(aquarium Fishes)
target_link_libraries(aquarium Plankton)


target_include_directories(aquarium PRIVATE src/Creature)
target_include_directories(aquarium PRIVATE src/Field)
target_include_directories(aquarium PRIVATE src/Fishes)
target_include_directories(aquarium PRIVATE src/Plankton)