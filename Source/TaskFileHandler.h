#ifndef HEADER_FILE_TASK_FILE_HANDLER
#define HEADER_FILE_TASK_FILE_HANDLER


#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif //WX_PRECOMP

#include <vector>

#include "TRTask.h"

class TaskFileHandler{
private:
    static const char *taskFile; 
public: 
    TaskFileHandler();
    ~TaskFileHandler();

    /* 
     * Load task in the file with relative direction specified by taskFile. 
     */
    std::vector<TRTask> LoadTask();
    /* 
     * Write task in the file with relative direction specified by taskFile. 
     */
    void WriteTask(const std::vector<TRTask> &tasks);
};

#endif //HEADER_FILE_TASK_FILE_HANDLER
