#include "TaskRecorderApp.h"
#include "BuildTaskPanel.h"

#include <iostream> 

bool TaskRecorderApp::OnInit() {
    TaskRecorderMainFrame* mainFrame = new TaskRecorderMainFrame(NULL, "Task Recorder"); 
    mainFrame->Show(true);
}

TaskRecorderApp::~TaskRecorderApp() {
}
wxIMPLEMENT_APP(TaskRecorderApp);
