#include "TaskHandler.h"

#include <iostream>
#include <stdexcept>

TaskHandler::TaskHandler() {
    taskIdx = 0;
    for(auto task : GetTasksFromFile()) {
        AddTask(task);
    }
}
TaskHandler::~TaskHandler(){
    SaveTasksToFile();
}

std::vector<TRTask> TaskHandler::GetTasksFromFile(){
    TaskFileHandler taskFileHandler; 
    return taskFileHandler.LoadTask();
}
std::vector<unsigned> TaskHandler::GetAllId() {
    std::vector<unsigned> Ids;
    for(auto task : tasks) {
        Ids.push_back(task.first);
    }
    return Ids;
}
std::vector<std::pair<int, TRTask>> TaskHandler::GetAllTasks() {
    std::vector<std::pair<int, TRTask>> taskVector;
    for(auto task : tasks) 
        taskVector.push_back(task);
    return taskVector;
}
void TaskHandler::SaveTasksToFile(){
    TaskFileHandler taskFileHandler; 
    std::vector<TRTask> writeTasks;

    for(auto i : tasks) {
        writeTasks.push_back(i.second);
    }
    taskFileHandler.WriteTask(writeTasks);
}
void TaskHandler::ModifiedTask(unsigned position, const TRTask &replaceTask) {
    auto ptr = tasks.find(position);
    try {
        if (ptr == tasks.end())
            throw std::out_of_range("Access unknown position");
        tasks[position] = replaceTask;
    } catch (const std::out_of_range &exc) {
        std::cerr << exc.what() << std::endl;
    }
}
unsigned TaskHandler::GetLength() {
    return tasks.size();
}
unsigned TaskHandler::GetMaxLength() {
    return TASK_LIMIT;
}

TRTask* TaskHandler::GetTaskAt(unsigned position) {
    ///will throw exception if position outside vector range
    auto ptr = tasks.find(position);
    if (ptr == tasks.end()) {

        //throw std::out_of_range("Access unknown position");
        return NULL;
    }
    return &tasks[position];
}

unsigned TaskHandler::AddTask(TRTask newTask) {
    //simple scheme to assign number. May overflow if add 2 ** 32 tasks in 1 session
    assert(GetLength() < GetMaxLength());
    tasks[taskIdx++] = newTask;
    return taskIdx - 1;
}
void TaskHandler::EraseTask(unsigned position) {
    assert(tasks.count(position));
    tasks.erase(position);
}


