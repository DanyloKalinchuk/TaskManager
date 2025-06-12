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

Json::Value SubTask::toJson() const{
    Json::Value root;

    root["name"] = this->name;
    root["status"] = tsk::status_to_string(this->status);
    root["description"] = this->description;

    return root;
}

std::unique_ptr<SubTask> SubTask::fromJson(const Json::Value& root){
    auto subtask = std::make_unique<SubTask>(root["name"].asString());

    if (tsk::status_map.find(root["status"].asString()) == tsk::status_map.end()){
        std::cout << "subtask status \n";
    }

    subtask->update_status(tsk::status_map.at(root["status"].asString()));
    subtask->update_description(root["description"].asString());

    return subtask;
}