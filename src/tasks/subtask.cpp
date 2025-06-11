#include <iostream>
#include "subtask.hpp"

SubTask::SubTask(const std::string name) :
    TaskBase(name){

    }

void SubTask::print_info(){
    std::cout << this->name + " info \n" <<
    "Name: " + this->name + "\n" <<
    "Status: " + tsk::status_to_string(this->status) + "\n" <<
    "Description:" + this->description + "\n";
}