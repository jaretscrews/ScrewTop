cmake_minimum_required(VERSION 3.16)
Project(ScrewTop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)

add_executable(ScrewTop app/app.cpp)

target_link_libraries(ScrewTop PRIVATE libScrewTopServer)
