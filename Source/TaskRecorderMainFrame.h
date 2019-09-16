#ifndef HEADER_TASK_RECORDER_MAIN_FRAME
#define HEADER_TASK_RECORDER_MAIN_FRAME


#include "TaskHandler.h"
#include "TaskListPanel.h"

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif //WX_PRECOMP

class TaskRecorderMainFrame : public wxFrame {
private:
    TaskHandler *taskHandler; 
    TaskListPanel *taskListPanel;
public:
    TaskRecorderMainFrame(wxWindow* parent, std::string frameName);
    void OnClose(wxCloseEvent &event);
};
#endif //HEADER_TASK_RECORDER_MAIN_FRAME
