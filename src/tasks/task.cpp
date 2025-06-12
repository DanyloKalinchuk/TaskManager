#include "task.hpp"


Task::Task(const std::string name):
    TaskBase(name),
    priority(Priority::LOW),
    deadline("None"){

    }

/*Get functions*/
Priority Task::get_priority() const{
    return this->priority;
}

std::string Task::get_deadline() const{
    return this->deadline;
}

int Task::get_subtask_num() const{
    return this->sub_tasks.size();
}

void Task::print_subtasks(){
    for (int i = 0; i < this->sub_tasks.size(); i++){
        std::cout << "\t" << i << " " << this->sub_tasks[i]->get_name() << "\n";
    }
}

void Task::print_info(){
    std::cout << "Name: " << this->name <<
    "\nStatus: " << tsk::status_to_string(this->status) <<
    "\nPriority: " << tsk::priority_to_string(this->priority) <<
    "\nDescription: " << get_description() << 
    "\nDeadline: " << this->deadline <<
    "\nSabtasks: \n";

    this->print_subtasks();
}

void Task::print_subtask_info(int num){
    this->sub_tasks[num]->print_info();
}

/*Update functions*/
void Task::update_priority(Priority priority){
    this->priority = priority;
}

void Task::update_deadline(std::string day, std::string month, std::string year){
    this->deadline = day + "/" + month + "/" + year;
}

void Task::update_deadline(){
    std::cout << "Day: ";
    std::string day;
    std::getline(std::cin, day);

    std::cout << "\nMonth: ";
    std::string month;
    std::getline(std::cin, month);

    std::cout << "\nYear: ";
    std::string year;
    std::getline(std::cin, year);
    std::cout << "\n";

    this->update_deadline(day, month, year);
}

void Task::update_subtask(int num){
    this->sub_tasks[num]->print_info();

    std::string parameter;
    while(true){
        std::cout << "Which parameter you want to change? \n\t NAME \n\t STATUS \n\t DESCRIPTION \n";
        std::getline(std::cin, parameter);

        if (parameter == "NAME" || parameter == "STATUS" || parameter == "DESCRIPTION"){
            break;
        }
        else{
            std::cout << "Provide correct parameter name \n";
        }
    }

    std::cout << "Print new value for the chosen parameter \n";
    std::string value;
    std::getline(std::cin, value);

    if (parameter == "NAME"){
        this->sub_tasks[num]->update_name(value);
    }
    else if (parameter == "STATUS"){
        Status status = tsk::status_map.at(value);
        this->sub_tasks[num]->update_status(status);
    }
    else{
        this->sub_tasks[num]->update_description(value);
    }
}

void Task::add_subtask(){
    std::string name;
    bool stop;
    do{
        stop = false;
        std::cout << "Print name for new subtask \n";
        std::getline(std::cin, name);

        for (const std::unique_ptr<SubTask>& sub_task : sub_tasks){
            if (sub_task->get_name() == name){
                std::cout << "Task with this name already exists \n";
                stop = true;
                break;
            }
        }
    }while(stop);

    std::unique_ptr<SubTask> st_ptr = std::make_unique<SubTask>(name);
    this->sub_tasks.push_back(std::move(st_ptr));
    std::cout << "Task succesfuly added \n";
}

void Task::del_subtask(){
    bool stop = true;
    while(stop){
        std::cout << "Print the name of subtask you want to delete \n";
        std::string name;
        std::getline(std::cin, name);

        for (int i = 0; i < this->sub_tasks.size(); i++){
            if (this->sub_tasks[i]->get_name() == name){
                this->sub_tasks.erase(this->sub_tasks.begin() + i);
                stop = false;
            }
        }
        if(stop){
            std::cout << "Task with this name does not exist \n";
        }
    }
    std::cout << "Task succesfuly deleted \n";
}

/*Json*/

Json::Value Task::toJson() const{
    Json::Value root;

    root["name"] = this->name;
    root["status"] = tsk::status_to_string(this->status);
    root["description"] = this->description;
    root["priority"] = tsk::priority_to_string(this->priority);
    root["deadline"] = this->deadline;

    Json::Value subtasks_arr(Json::arrayValue);
    for(const auto& subtask : this->sub_tasks){
        subtasks_arr.append(subtask->toJson());
    }
    root["sub_tasks"] = subtasks_arr;

    return root;
}

std::unique_ptr<Task> Task::fromJson(const Json::Value& root){
    auto task = std::make_unique<Task>(root["name"].asString());

    task->status = tsk::status_map.at(root["status"].asString());
    task->description = root["description"].asString();
    task->priority = tsk::priority_map.at(root["priority"].asString());
    task->deadline = root["deadline"].asString();

    const Json::Value& subtasks_arr = root["sub_tasks"];
    for (const auto& subtask_json : subtasks_arr){
        task->sub_tasks.push_back(SubTask::fromJson(subtask_json));
    }

    return task;
}