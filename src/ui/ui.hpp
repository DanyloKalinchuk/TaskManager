#pragma once

#include "../tasks/tasks_list.hpp"

void clear_screen();

namespace menu{
    void main_screen();
    void choose_task();
    void change_task(std::string);
    void change_subtasks(std::string);
    void info();
};