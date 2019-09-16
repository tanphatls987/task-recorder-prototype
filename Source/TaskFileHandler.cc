#include <fstream>
#include <iostream>

#include "TaskFileHandler.h"

const char *TaskFileHandler::taskFile = "doneTask.txt"; 
std::vector<TRTask> TaskFileHandler::LoadTask() {
    std::ifstream input(taskFile, std::ifstream::in); 
    std::vector<TRTask> tasks;

    std::string tmp;
    while (input >> tmp, tmp == "[BEGIN]") {
        input.ignore();
        std::string taskStr;

        while (true) {
            std::getline(input, tmp);
            if (tmp == "[END]") break;
            taskStr += tmp + "\n";
        } 
        
        TRTask newTask;
        newTask.Make(taskStr);
        tasks.push_back(newTask);
    }
    input.close();
    return tasks;
}
void TaskFileHandler::WriteTask(const std::vector<TRTask> &tasks){
    std::ofstream output(taskFile, std::ofstream::out); 
    for(TRTask task : tasks) 
        output << "[BEGIN]\n" + task.ToString() + "[END]\n";
    output.close();
}
TaskFileHandler::TaskFileHandler(){
}
TaskFileHandler::~TaskFileHandler() {
}
    
