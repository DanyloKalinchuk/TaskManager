#include "task.hpp"

extern std::map<std::string, std::unique_ptr<Task>> tasks_map;

namespace controls{
    void add_task();
    void del_task();
    void print_tasks();

    void print_by_parameter(Status);
    void print_by_parameter(Priority);
};