#include <stdlib.h> 
#include <iostream>
#include "tasks_list.hpp"

std::map<std::string, std::unique_ptr<Task>> tasks_map;

void controls::add_task(){
    bool stop;

    do{
        stop = false;

        std::cout << "Print name of a new task \n";
        std::string name;
        std::getline(std::cin, name);

        if (tasks_map.find(name) == tasks_map.end()){
            tasks_map.emplace(name, std::make_unique<Task>(name));
            stop = true;
        }
        else{
            std::cout << "Task with this name already exists \n";
        }
    }while(!stop);


}

void controls::del_task(){
    bool stop;

    do{
        stop = false;

        controls::print_tasks();

        std::cout << "Print the name of the task you want to delete or _exit_ to return \n";
        std::string name;
        std::getline(std::cin, name);

        if (name == "_exit_"){
            stop = true;
        }else if (tasks_map.find(name) == tasks_map.end()){
            std::cout << "Not a valid name \n";
        }else{
            tasks_map.erase(name);
            stop = true;
        }
    }while(!stop);
}

void controls::print_tasks(){
    if (tasks_map.size() > 0){
        for (const auto& [task_name, task_ptr] : tasks_map){
            std::cout << "\t" << task_name << "\n";
        }
    }
    else{
        std::cout << "No tasks found \n";
    }
}