cmake_minimum_required(VERSION 3.30)
project(TP3_BALDE_TALHATOU)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)


add_executable(TP3_BALDE_TALHATOU
        main.cpp
        Device.cpp
        Machine.cpp
        Team.cpp
        Manager.cpp)

add_custom_command(TARGET TP3_BALDE_TALHATOU POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/assets $<TARGET_FILE_DIR:TP3_BALDE_TALHATOU>/assets
)