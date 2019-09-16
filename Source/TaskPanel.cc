#include <wx/datetime.h> 

#include "TaskPanel.h"
#include "BuildTaskDialog.h"


TaskPanel::TaskPanel(wxWindow *parent, TaskHandler *taskHandler, unsigned taskId) :
    wxPanel(parent) { 
this->taskHandler = taskHandler;
    this->taskId = taskId;
    taskButton = new wxButton(this, wxID_ANY, GetTaskInfo(), wxDefaultPosition, wxDefaultSize, wxBU_LEFT);
    dropDown = new TaskButtonDropDown(this);
    SetOwnBackgroundColour(*wxWHITE); 
    Refresh();
        
    MakeSizer();
    BindControl();
}

wxBoxSizer* TaskPanel::MakeSizer() {
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL); 
    sizer->Add(taskButton, 0, wxEXPAND);
    sizer->Add(dropDown, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
    SetSizer(sizer);

    dropDown->Hide();
    //sizer->Detach(dropDown);
    sizer->Layout();

    return sizer;
}

void TaskPanel::BindControl() {
    int taskButtonId = taskButton->GetId();
    Bind(wxEVT_BUTTON, &TaskPanel::OnClickTaskButton, this, taskButtonId, taskButtonId);
    
    int playButtonId = dropDown->GetTimerPlayButton()->GetId();
    Bind(wxEVT_BUTTON, &TaskPanel::OnClickPlayButton, this, playButtonId, playButtonId);
    int pauseButtonId = dropDown->GetTimerPauseButton()->GetId();
    Bind(wxEVT_BUTTON, &TaskPanel::OnClickPauseButton, this, pauseButtonId, pauseButtonId);
    int stopButtonId = dropDown->GetTimerStopButton()->GetId();
    Bind(wxEVT_BUTTON, &TaskPanel::OnClickStopButton, this, stopButtonId, stopButtonId);
    int eraseButtonId = dropDown->GetTimerEraseButton()->GetId();
    Bind(wxEVT_BUTTON, &TaskPanel::OnClickEraseButton, this, eraseButtonId, eraseButtonId);

    int menuAddId = dropDown->GetMenuAdd()->GetId();
    Bind(wxEVT_MENU, &TaskPanel::OnClickAddMenu, this, menuAddId, menuAddId);
    int menuQuickAddId = dropDown->GetMenuQuickAdd()->GetId();
    Bind(wxEVT_MENU, &TaskPanel::OnClickQuickAddMenu, this, menuQuickAddId, menuQuickAddId);

    int menuCommitId = dropDown->GetMenuCommit()->GetId();
    Bind(wxEVT_MENU, &TaskPanel::OnClickCommitMenu, this, menuCommitId, menuCommitId);
    int menuQuickCommitId = dropDown->GetMenuQuickCommit()->GetId();
    Bind(wxEVT_MENU, &TaskPanel::OnClickQuickCommitMenu, this, menuQuickCommitId, menuQuickCommitId);

    int menuDeleteId = dropDown->GetMenuDelete()->GetId();
    Bind(wxEVT_MENU, &TaskPanel::OnClickDeleteMenu, this, menuDeleteId, menuDeleteId);
    int menuModifyId = dropDown->GetMenuModify()->GetId();
    Bind(wxEVT_MENU, &TaskPanel::OnClickModifyMenu, this, menuModifyId, menuModifyId);
}

std::string TaskPanel::GetDisplayTime(int time) {
    assert(time >= 0);
    int ss = time % 60; time /= 60;
    int mm = time % 60; time /= 60;
    int hh = time % 24; time /= 24;
    int dd = time;
    std::ostringstream ostr;

    bool timeOn = false;
    timeOn |= dd > 0;
    if (timeOn) ostr << dd << "d";
    timeOn |= hh > 0;
    if (timeOn) ostr << hh << "h";
    timeOn |= mm > 0;
    if (timeOn) ostr << mm << "m";
    ostr << ss << "s";
    return ostr.str();
}
wxString TaskPanel::GetTaskInfo() {
    TRTask* task = taskHandler->GetTaskAt(taskId); 
    wxString info = task->GetName();
    if (task->GetDisplayTimeDone()) {
        unsigned timeDone = task->GetTimeDone();
        info += "\nCommit: " + std::to_string(timeDone) + " time";
    }
    if (task->GetDisplayLastDone()) {
        time_t lastDone = task->GetLastDone();
        char buffer[30];
        strftime(buffer, 29, "%c", localtime(&lastDone));
        info += "\nLast commit: " + std::string(buffer);
    }
    if (task->GetDisplayTimeElapsed()) {
        int timeElapsed = task->GetTimeElapsed();
        info += "\nTime recorded: " + GetDisplayTime(timeElapsed);
    }
    return info;

}

void TaskPanel::OnClickTaskButton(wxCommandEvent &event) {
    int dropDownShowStatus = dropDown->IsShown();
    if (dropDownShowStatus == true) {
        dropDown->HideWithEffect(wxSHOW_EFFECT_SLIDE_TO_TOP);
        //GetSizer()->Detach(dropDown);
        GetSizer()->Layout();
    } else {
        dropDown->ShowWithEffect(wxSHOW_EFFECT_SLIDE_TO_BOTTOM);
        //GetSizer()->Insert(1, dropDown, 0, wxALIGN_RIGHT | wxALIGN_CENTER_VERTICAL);
    }
    GetGrandParent()->Layout(); /// a bit risky
}
void TaskPanel::OnUpdate() {
    ///this only handle task button
    ///right now it rely on the fact that it is only called when stop or play
    taskButton->SetLabel(GetTaskInfo());
    dropDown->SetTimerDisplayValue("0s");
    GetGrandParent()->Layout(); /// a bit risky
}

void TaskPanel::UpdateTaskName(const std::string &name) {
    TRTask* task = GetTask();
    task->SetName(name);
    OnUpdate();
}
/*
int TaskPanel::GetRunningTime(time_t currentTime) {
    TRTask *task = GetTask();
    if (!task->IsRecording()) {
        return -1;
    } else {
        return task->GetRecordingTime(currentTime);
    }
        
}
*/
void TaskPanel::UpdateRunningTime(time_t currentTime) {
    TRTask* task = GetTask();
    if (task->IsRecording()) {
        int time = task->GetRecordingTime(currentTime);  
        std::string timeStr = GetDisplayTime(time); 
        dropDown->SetTimerDisplayValue(timeStr); 
    }
}

TRTask* TaskPanel::GetTask() const {
    return taskHandler->GetTaskAt(taskId);
}
bool TaskPanel::IsValid() {
    return GetTask() != NULL; 
}
void TaskPanel::OnClickPlayButton(wxCommandEvent &event) {
    //std::cerr << "Play button clicked\n";
    TRTask* task = GetTask();

    //std::cerr << "Get task OK\n";
    
    if (task->IsIdle()) {
        task->StartRecord();
        //std::cerr << "Call update\n";
        OnUpdate();
    } else if (task->IsPausing()) {
        task->UnpauseRecord();
    }
}
void TaskPanel::OnClickPauseButton(wxCommandEvent &event) {
    GetTask()->PauseRecord();
}
void TaskPanel::OnClickStopButton(wxCommandEvent &event) {
    //std::cerr << "Stop button clicked\n";
    GetTask()->StopRecord(true); 
    OnUpdate();
}
void TaskPanel::OnClickEraseButton(wxCommandEvent &event) {
    GetTask()->StopRecord(false);
    OnUpdate();
}
void TaskPanel::OnClickAddMenu(wxCommandEvent &event) {
    ///I guess this call for a new class
}
void TaskPanel::OnClickQuickAddMenu(wxCommandEvent &event) {
    GetTask()->AddTimeDone();
    OnUpdate();
}
void TaskPanel::OnClickCommitMenu(wxCommandEvent &event) {
}
void TaskPanel::OnClickQuickCommitMenu(wxCommandEvent &event) {
    GetTask()->QuickCommit();
    OnUpdate();
}
void TaskPanel::OnClickModifyMenu(wxCommandEvent &event) {
    BuildTaskDialog *modifyDialog = new BuildTaskDialog(this, GetTask(), "Modify task");
    std::vector<wxString> banName;
    for(auto task : taskHandler->GetAllTasks()) {
        if (task.first != taskId) {
            banName.push_back(task.second.GetName());
        }
    }
    modifyDialog->SetExcludedNameList(banName);
    if (modifyDialog->ShowModal()) {
        OnUpdate();
    }
}
void TaskPanel::OnClickDeleteMenu(wxCommandEvent &event) {
    ///is there something better than just hide the panel and detach it from the sizer

    Hide();
    GetParent()->GetSizer()->Detach(this); 
    GetParent()->Layout();
    taskHandler->EraseTask(taskId); 
}
bool TaskPanel::IsDisplayable(bool focusMode, std::string prefix) {
    if (focusMode && !GetTask()->IsActive()) {
        return false;
    }
    if (!GetTask()->HavePrefix(prefix)) {
        return false;
    }
    return true;
}

TaskPanel::~TaskPanel() {
}
