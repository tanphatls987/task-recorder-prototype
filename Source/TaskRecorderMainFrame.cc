#include "TaskRecorderMainFrame.h"

//TaskRecorderMainFrame::
TaskRecorderMainFrame::TaskRecorderMainFrame(wxWindow* parent, std::string frameName) 
    : wxFrame(parent, wxID_ANY, frameName, wxDefaultPosition, wxSize(600, 800)) {
    taskHandler = new TaskHandler();
    taskListPanel = new TaskListPanel(this, taskHandler);
    Bind(wxEVT_CLOSE_WINDOW, &TaskRecorderMainFrame::OnClose, this, GetId(), GetId());
}
void TaskRecorderMainFrame::OnClose(wxCloseEvent &event) {
    taskHandler->SaveTasksToFile();
    delete(taskHandler); 
    Destroy();
}
