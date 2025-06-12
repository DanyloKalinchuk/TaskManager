#include "task_base.hpp"
#include <iostream>


const std::map<std::string, Status> tsk::status_map = {
    {"DONE", Status::DONE},
    {"IN_PROGRESS", Status::IN_PROGRESS}
};

const std::map<std::string, Priority> tsk::priority_map = {
    {"HIGH", Priority::HIGH},
    {"LOW", Priority::LOW}
};

std::string tsk::status_to_string(Status status){
    switch (status)
    {
    case Status::DONE :
        return "DONE";
        
    case Status::IN_PROGRESS :
        return "IN_PROGRESS";

    default:
        return "Invalid status value";
    }
}

std::string  tsk::priority_to_string(Priority priority){
    switch (priority)
    {
    case Priority::HIGH :
        return "HIGH";
        
    case Priority::LOW :
        return "LOW";

    default:
        return "Invalid priority value";
    }
}


TaskBase::TaskBase(const std::string name) :
    name(name),
    status(Status::IN_PROGRESS),
    description("DO " + name){
        
    }

std::string TaskBase::get_name() const{
    return this->name;
}

Status TaskBase::get_status() const{
    return this->status;
}

std::string TaskBase::get_description() const{
    return this->description;
}

void TaskBase::update_name(std::string name){
    this->name = name;
}

void TaskBase::update_status(Status status){
    this->status = status;
}

void TaskBase::update_description(std::string description){
    this->description = description;
}