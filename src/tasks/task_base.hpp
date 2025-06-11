#pragma once

#include <string>
#include <map>

enum Status{
    DONE,
    IN_PROGRESS
};

enum Priority{
    HIGH,
    LOW
};

namespace tsk{
    extern const std::map<std::string, Status> status_map;
    extern const std::map<std::string, Priority> priority_map;

    std::string status_to_string(Status status);
    std::string priority_to_string(Priority priority);
};

class TaskBase{
    protected:
    std::string name;
    Status status;
    std::string description;

    public:
    TaskBase(const std::string);
    virtual ~TaskBase() = default;

    std::string get_name() const;
    Status get_status() const;
    std::string get_description() const;
    void virtual print_info() = 0;

    void update_name(std::string);
    void update_status(Status);
    void update_description(std::string);   
};