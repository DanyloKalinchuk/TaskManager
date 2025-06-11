cmake_minimum_required(VERSION 3.10)

project(TaskManager)

set(CMAKE_CXX_STANDARD 17)

add_executable(TaskManager
    src/main.cpp 
    src/tasks/task.cpp
    src/tasks/tasks_list.cpp
    src/tasks/task_base.cpp
    src/tasks/subtask.cpp
    src/ui/ui.cpp
)
