#pragma once

#include <vector>
#include <memory>
#include "subtask.hpp"


class Task : public TaskBase{
    Priority priority;
    std::string deadline = "\0";
    std::vector<std::unique_ptr<SubTask>> sub_tasks;

    public:
    Task(const std::string);
    virtual ~Task() = default;

    Task(Task&&) = default;
    Task& operator=(Task&&) = default;

    Task(const Task&) = delete;
    Task& operator=(const Task&) = delete;

    Priority get_priority() const;
    std::string get_deadline() const;
    int get_subtask_num() const;
    void print_info() override;
    void print_subtasks();
    void print_subtask_info(int);

    void update_priority(Priority);
    void update_deadline();
    void update_deadline(std::string, std::string, std::string);
    void update_subtask(int);

    void add_subtask();
    void del_subtask();
};