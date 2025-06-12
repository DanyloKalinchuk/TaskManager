#include "in_out.hpp"

void in_out::read(){
    std::fstream input("tasks.json");

    if (input.is_open()){
        Json::Reader reader;
        Json::Value root;

        if (reader.parse(input, root)){
            tasks_map.clear();

            for (const auto& task_json : root){
                auto task = Task::fromJson(task_json);
                tasks_map.emplace(task->get_name(), std::move(task));
            }
        }
    }

    input.close();
}

void in_out::write(){
    Json::Value root(Json::arrayValue);

    for (const auto& [name, task] : tasks_map){
        root.append(task->toJson());
    }

    std::ofstream output("tasks.json");

    output << root;

    output.close();
}