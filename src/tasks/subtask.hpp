#pragma once

#include "task_base.hpp"

class SubTask : public TaskBase{
    public:
    SubTask(const std::string);
    virtual ~SubTask() = default;

    void print_info() override;

    Json::Value toJson() const;
    static std::unique_ptr<SubTask> fromJson(const Json::Value&);
};
