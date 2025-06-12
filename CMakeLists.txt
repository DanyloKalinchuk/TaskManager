
cmake_minimum_required(VERSION 3.10)

set(CMAKE_TOOLCHAIN_FILE "D:/C++ projects/TaskManager-main/vcpkg/scripts/buildsystems/vcpkg.cmake")

project(TaskManager)

set(CMAKE_CXX_STANDARD 17)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    set(VCPKG_TARGET_TRIPLET "x64-mingw-static")
    set(JSONCPP_ROOT "D:/C++ projects/TaskManager-main/vcpkg/installed/x64-mingw-static")
else()
    set(VCPKG_TARGET_TRIPLET "x64-windows")
    set(JSONCPP_ROOT "D:/C++ projects/TaskManager-main/vcpkg/installed/x64-windows")
endif()

find_path(JSONCPP_INCLUDE_DIR 
    NAMES json/json.h
    PATHS ${JSONCPP_ROOT}/include
    NO_DEFAULT_PATH
)

find_library(JSONCPP_LIBRARY 
    NAMES jsoncpp libjsoncpp jsoncpp_static
    PATHS ${JSONCPP_ROOT}/lib
    NO_DEFAULT_PATH
)

add_executable(TaskManager
    src/main.cpp
    src/tasks/task.cpp
    src/tasks/tasks_list.cpp
    src/tasks/task_base.cpp
    src/tasks/subtask.cpp
    src/ui/ui.cpp
    src/in_out/in_out.cpp
)

if(JSONCPP_INCLUDE_DIR AND JSONCPP_LIBRARY)
    target_include_directories(TaskManager PRIVATE ${JSONCPP_INCLUDE_DIR})
    target_link_libraries(TaskManager PRIVATE ${JSONCPP_LIBRARY})
    message(STATUS "JsonCpp found!")
    message(STATUS "Include: ${JSONCPP_INCLUDE_DIR}")
    message(STATUS "Library: ${JSONCPP_LIBRARY}")
    message(STATUS "Using triplet: ${VCPKG_TARGET_TRIPLET}")
else()
    message(FATAL_ERROR "JsonCpp not found!")
    message(STATUS "Include: ${JSONCPP_INCLUDE_DIR}")
    message(STATUS "Library: ${JSONCPP_LIBRARY}")
    message(STATUS "Searched in: ${JSONCPP_ROOT}")
endif()
