#include <iostream>
#include "ui.hpp"

void clear_screen() {
    std::cout << "\x1B[2J\x1B[H";
    std::cout.flush();
}

void menu::main_screen(){
    clear_screen();

    bool stop = false;
    while (!stop){
        std::cout << "Print number of needed action:\n" <<
        "\t\'1\' see existing tasks \n" <<
        "\t\'2\' change existing task \n" <<
        "\t\'3\' add new task \n" <<
        "\t\'4\' delete task \n" <<
        "\t\'5\' get info \n" <<
        "\tor \'0\' to close the app \n";
        char action;
        std::cin >> action;
        std::cin.ignore();

        switch (action - '0'){
            case 1 :
                clear_screen();
                std::cout << "Tasks: \n";
                controls::print_tasks();
                break;
            case 2 :
                if (tasks_map.size() > 0){
                    menu::choose_task();
                }else{
                    clear_screen();
                    std::cout << "No tasks found \n";
                }
                break;
            case 3 :
                controls::add_task();
                clear_screen();
                std::cout << "Task successfuly added \n";
                break;
            case 4 :
                controls::del_task();
                clear_screen();
                std::cout << "Task successfuly deleted \n";
                break;
            case 5 :
                menu::info();
                break;
            case 0 :
                stop = true;
                break;
            default:
                std::cout << "Invalid input";
        }
    }       
}

void menu::choose_task(){
    clear_screen();
    if (tasks_map.size() > 0){
        std::cout << "Tasks: \n";
        controls::print_tasks();

        bool stop;
        do{
            stop = false;

            std::cout << "Choose task by name \n";
            std::string name;
            std::getline(std::cin, name);

            if (tasks_map.find(name) == tasks_map.end()){
                std::cout << "Task with name \"" + name + "\" does not exist";
            }else{
                stop = true;
                menu::change_task(name);
            }

        }while(!stop);
    }
}

void menu::change_task(std::string name){
    clear_screen();
    std::cout << name << " info \n";
    tasks_map[name]->print_info();

    std::cout << "Choose parameter to change by number \n" <<
    "\t\'1\' Name \n" <<
    "\t\'2\' Status \n" <<
    "\t\'3\' Description \n" <<
    "\t\'4\' Priority \n" <<
    "\t\'5\' Deadline \n" <<
    "\t\'6\' Subtask\n";

    char action;
    std::cin >> action;
    std::cin.ignore();

    switch (action - '0'){
        case 1 :{
            std::cout << "Print new name";
            std::string new_name;
            std::getline(std::cin, new_name);

            std::unique_ptr<Task> task_ptr = std::move(tasks_map[name]);
            tasks_map.erase(name);
            task_ptr->update_name(new_name);
            tasks_map.emplace(new_name, std::move(task_ptr));
            break;
        }
        case 2 :{
            std::cout << "Possible status values: \n";
            for (const auto& [status, enum_value] : tsk::status_map){
                std::cout << "\t" << status << "\n";
            }

            bool stop;
            do{
                stop = false;
                std::cout << "Print new status \n";
                std::string status;
                std::cin >> status;
                std::cin.ignore();
                
                if (tsk::status_map.find(status) == tsk::status_map.end()){
                    std::cout << "Invalid status provided \n";
                }
                else{
                    stop = true;
                    tasks_map[name]->update_status(tsk::status_map.at(status));
                }

            }while(!stop);
            break;
        }
        case 3 :{
            std::cout << "Print new description \n";

            std::string description;
            std::getline(std::cin, description);

            tasks_map[name]->update_description(description);
            break;
        }

        case 4 :{
            std::cout << "Possible priority values: \n";
            for (const auto& [priority, enum_value] : tsk::priority_map){
                std::cout << "\t" << priority << "\n";
            }

            bool stop;
            do{
                stop = false;
                std::cout << "Print new prioity \n";
                std::string priority;
                std::cin >> priority;
                std::cin.ignore();
                
                if (tsk::priority_map.find(priority) == tsk::priority_map.end()){
                    std::cout << "Invalid priority provided \n";
                }
                else{
                    stop = true;
                    tasks_map[name]->update_priority(tsk::priority_map.at(priority));
                }

            }while(!stop);
            break;          
        }
        case 5 :
            tasks_map[name]->update_deadline();
            break;
        case 6 :
            change_subtasks(name);
            break;
        

    }   
}

void menu::change_subtasks(std::string name){
    clear_screen();
    std::cout << "Print number of needed action:\n" <<
    "\t\'1\' Update existing subtask \n" <<
    "\t\'2\' Add subtask \n" <<
    "\t\'3\' Delete subtask \n";

    char action;
    std::cin >> action;
    std::cin.ignore();

    switch (action - '0'){
        case 1 :{
                if (tasks_map[name]->get_subtask_num() > 0){
                    bool stop;
                    do{
                        stop = false;

                        std::cout << "Subtasks list: \n";
                        tasks_map[name]->print_subtasks();

                        std::cout << "Choose subtask by number \n";
                        char subtask;
                        std::cin >> subtask;
                        std::cin.ignore();

                        if ((subtask - '0') >= tasks_map[name]->get_subtask_num() || (subtask - '0') < 0){
                            std::cout << "Invalid subtask number \n";
                        }else{
                            stop = true;
                            tasks_map[name]->update_subtask(subtask - '0');
                        }

                    }while(!stop);
                }else{
                    clear_screen();
                    std::cout << "No subtasks found \n";
                }

            break;
        }

        case 2 :
            tasks_map[name]->add_subtask();
            break;

        case 3 :
            std::cout << "Subtasks list: \n";
            tasks_map[name]->print_subtasks();
            
            tasks_map[name]->del_subtask();
            break;
        
        default:
            std::cout << "Invalid command \n";
            menu::change_subtasks(name);
            break;

    }   
}

void menu::info(){
    clear_screen();
    std::cout << "Which information do you need?\n" <<
    "\t\'1\' Task information \n" <<
    "\t\'2\' Tasks in progress \n" <<
    "\t\'3\' Done tasks \n" <<
    "\t\'4\' High priority tasks \n" <<
    "\t\'5\' Low priority tasks \n";

    char action;
    std::cin >> action;
    std::cin.ignore();

    switch (action - '0'){
        case 1 :{
            bool stop;
            do{
                stop = false;
                controls::print_tasks();
                std::cout << "Choose task by name \n";

                std::string name;
                std::getline(std::cin, name);

                if (tasks_map.find(name) == tasks_map.end()){
                    std::cout << "Not a valid name \n";
                }else{
                    tasks_map[name]->print_info();
                    stop = true;
                }
            }while(!stop);
            break;
        }
        case 2 :
            std::cout << "Task with IN_PROGRESS status: \n";
            controls::print_by_parameter(Status::IN_PROGRESS);
            break;
        case 3 :
            std::cout << "Tasks with DONE status: \n";
            controls::print_by_parameter(Status::DONE);
            break;
        case 4 :
            std::cout << "Tasks with high priority: \n";
            controls::print_by_parameter(Priority::HIGH);
            break;
        case 5 :
            std::cout << "Tasks with low priority: \n";
            controls::print_by_parameter(Priority::LOW);
            break;

    }
}

void controls::print_by_parameter(Status status){
    for (const auto& [name, ptr] : tasks_map){
        if (ptr->get_status() == status){
            std::cout << "\t" << ptr->get_name() << "\n";
        }
    }

}

void controls::print_by_parameter(Priority priority){
    for (const auto& [name, ptr] : tasks_map){
        if (ptr->get_priority() == priority){
            std::cout << "\t" << ptr->get_name() << "\n";
        }
    }    
}