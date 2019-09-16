#ifndef HEADER_TASKHANDLER
#define HEADER_TASKHANDLER

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif //WX_PRECOMP

#include <map>
#include <vector>

#include "TaskFileHandler.h"
/*
 * All operation on task should go through this class.
 */
class TaskHandler{
private:
    static const int TASK_LIMIT = 100000;
    std::map<unsigned, TRTask> tasks; ///do I even need to store this task list?
    int taskIdx;
public:
    TaskHandler();
    ~TaskHandler();

    //bool CanAddTask(const TRTask &newTask);
    

    unsigned AddTask(TRTask newTask); 
    void ModifiedTask(unsigned position, const TRTask &replaceTask);
    void EraseTask(unsigned position);
    std::vector<TRTask> GetTasksFromFile();
    void SaveTasksToFile();

    unsigned GetLength();
    TRTask* GetTaskAt(unsigned position);

    std::vector<unsigned> GetAllId();
    unsigned GetMaxLength();
    std::vector<std::pair<int, TRTask>> GetAllTasks();


    //there will be some validators later
};
#endif //HEADER_TASKHANDLER

