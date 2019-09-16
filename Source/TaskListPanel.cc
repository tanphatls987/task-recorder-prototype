#include <algorithm> 

#include "TaskListPanel.h"

TaskListPanel::TaskListPanel(wxWindow *parent, TaskHandler *taskHandler) :
    wxPanel(parent) {
    this->taskHandler = taskHandler;
    

    taskListWindow = new wxScrolled<wxWindow>(this, wxID_ANY,
        wxDefaultPosition, wxDefaultSize, wxVSCROLL | wxBORDER_SIMPLE);
    taskListWindow->SetOwnBackgroundColour(*wxWHITE);
    taskListWindow->SetScrollbars(20, 20, 200, 200);
    taskListWindow->Refresh();
    taskListWindow->Layout();

    taskListWindow->SetSizer(new wxBoxSizer(wxVERTICAL));


    LoadExistTask();
    CreateToolMenu();
    CreateAppearance();
    BindControl();
    SetTimer();
}   

void TaskListPanel::OnTimerNotify(wxTimerEvent& event) {
    time_t currentTime = time(NULL);
    for(auto &tmp : taskListWindow->GetChildren()) {
        TaskPanel* taskPanel = (TaskPanel*) tmp;
        if (taskPanel->IsValid()) {
            taskPanel->UpdateRunningTime(currentTime);
        }
    }
}
void TaskListPanel::SetTimer() {
    this->taskTimer = new wxTimer(this, wxID_ANY);
    int timerId = taskTimer->GetId();
    Bind(wxEVT_TIMER, &TaskListPanel::OnTimerNotify, this, timerId, timerId);
    int notifyInterval = 1000;
    taskTimer->Start(notifyInterval);
}
void TaskListPanel::LoadExistTask() {
    std::vector<unsigned> taskIds = taskHandler->GetAllId();
    for(auto Id : taskIds) 
        AddExistTask(Id);
}

void TaskListPanel::SaveTask() {
}
void TaskListPanel::CreateAppearance() {
    wxBoxSizer* sizer = new wxBoxSizer(wxVERTICAL);

    int itemBorder = 20;
    int itemFlag = wxLEFT | wxRIGHT | wxEXPAND;

    sizer->AddSpacer(30);
    sizer->Add(toolPanel, 0, itemFlag | wxALIGN_BOTTOM, itemBorder);
    sizer->AddSpacer(10);
    sizer->Add(taskListWindow, 1, itemFlag, itemBorder);
    sizer->AddSpacer(30);
    SetSizer(sizer);
}

void TaskListPanel::CreateToolMenu() {
    ///should create and also bind event handler
    toolPanel = new TaskListToolPanel(this);

}


void TaskListPanel::AddExistTask(unsigned taskId) {
    wxSizer* sizer = taskListWindow->GetSizer();
    assert(sizer != NULL);
    int itemGap = 0;
    int itemFlag = wxBOTTOM | wxEXPAND;
    sizer->Add(new TaskPanel(taskListWindow, taskHandler, taskId), 0, itemFlag, itemGap);

}
void TaskListPanel::AddNewTask(TRTask newTask) {
    int taskId = taskHandler->AddTask(newTask);
    AddExistTask(taskId);
}

void TaskListPanel::OnClose(wxCommandEvent &event) {
}
void TaskListPanel::OnClickAddButton(wxCommandEvent& event) {
    TRTask potentialNewTask;
    BuildTaskDialog* buildTaskDialog = new BuildTaskDialog(this, &potentialNewTask, "Add New Task");
    std::vector<wxString> banName;

    for(auto task : taskHandler->GetAllTasks()) {
        banName.push_back(task.second.GetName());
    }
    buildTaskDialog->SetExcludedNameList(banName);
    int retCode = buildTaskDialog->ShowModal();
    if (retCode == wxID_OK) {
        AddNewTask(potentialNewTask);
        wxCommandEvent tmp;
        OnSortOptionSelected(tmp);
    }
}
void TaskListPanel::FilterTask() {
    std::vector<TaskPanel*> taskListPanel = GetAllTaskPanel();
    //taskListWindow->RemoveAllChildren(); 

    std::string prefix = toolPanel
        ->GetTaskSearchCtrl()
        ->GetValue()
        .ToStdString();  
    bool focusMode = toolPanel
        ->GetFocusCtrl()
        ->GetValue();
    for(auto taskPanel : taskListPanel) {
        bool accept = taskPanel->IsDisplayable(focusMode, prefix);
        taskPanel->Show(accept); 
    }
    taskListWindow->Layout();
}
void TaskListPanel::OnClickFocusModeCheckBox(wxCommandEvent& event) {
    FilterTask();     
}
void TaskListPanel::OnChangeSearchBox(wxCommandEvent& event) {
    FilterTask();
}
bool TaskListPanel::TaskPanelNameComparator(const TaskPanel* p1, const TaskPanel *p2) {
    return p1->GetTask()->GetName() < p2->GetTask()->GetName();
}
bool TaskListPanel::TaskPanelDurationComparator(const TaskPanel* p1, const TaskPanel *p2) {
    TRTask *task1 = p1->GetTask(), *task2 = p1->GetTask();
    if (task1->GetTimeElapsed(false) == task2->GetTimeElapsed(false)) {
        return task1->GetName() < task2->GetName();
    }
    return task1->GetTimeElapsed(false) < task2->GetTimeElapsed(false);
}
bool TaskListPanel::TaskPanelLastCommitComparator(const TaskPanel* p1, const TaskPanel *p2) {
    TRTask *task1 = p1->GetTask(), *task2 = p1->GetTask();
    if (task1->GetLastDone(false) == task2->GetLastDone(false)) {
        return task1->GetName() < task2->GetName();
    }
    return task1->GetLastDone(false) < task2->GetLastDone(false);
}
void TaskListPanel::OnOrderOptionSelected(wxCommandEvent &event) {
    OnSortOptionSelected(event);
}
void TaskListPanel::OnSortOptionSelected(wxCommandEvent& event) {
    std::vector<TaskPanel*> taskPanelList = GetAllTaskPanel();
    for(auto taskPanel : taskPanelList) {
        taskListWindow->GetSizer()->Detach(taskPanel); 
    }
    if (toolPanel->IsSortByNameSelected()) {
        std::sort(taskPanelList.begin(), taskPanelList.end(), TaskPanelNameComparator);
    }
    if (toolPanel->IsSortByDurationSelected()) {
        std::sort(taskPanelList.begin(), taskPanelList.end(), TaskPanelDurationComparator);
    }
    if (toolPanel->IsSortByLastCommitSelected()) {
        std::sort(taskPanelList.begin(), taskPanelList.end(), TaskPanelLastCommitComparator);
    }

    if (toolPanel->IsDescendingSelected()) {
        reverse(taskPanelList.begin(), taskPanelList.end());
    }
    
    int itemGap = 0;
    int itemFlag = wxBOTTOM | wxEXPAND;
    for(auto taskPanel : taskPanelList) {
        taskListWindow->GetSizer()->Add(taskPanel, 0, itemFlag, itemGap);    
    }
    FilterTask();
}
void TaskListPanel::BindControl() {
    int buttonAddId = toolPanel->GetAddButton()->GetId(); 
    Bind(wxEVT_BUTTON, &TaskListPanel::OnClickAddButton, this, 
        buttonAddId, buttonAddId); 
    
    int focusModeCheckBoxId = toolPanel->GetFocusCtrl()->GetId();
    Bind(wxEVT_CHECKBOX, &TaskListPanel::OnClickFocusModeCheckBox, this,
        focusModeCheckBoxId, focusModeCheckBoxId);

    int taskSearchCtrlId = toolPanel->GetTaskSearchCtrl()->GetId();
    Bind(wxEVT_TEXT, &TaskListPanel::OnChangeSearchBox, this,
        taskSearchCtrlId, taskSearchCtrlId);


    int optionByNameMenuId = toolPanel->GetOptionByNameMenu()->GetId(); 
    Bind(wxEVT_MENU, &TaskListPanel::OnSortOptionSelected, this,
        optionByNameMenuId, optionByNameMenuId);
    int optionByDurationMenuId = toolPanel->GetOptionByDurationMenu()->GetId(); 
    Bind(wxEVT_MENU, &TaskListPanel::OnSortOptionSelected, this,
        optionByDurationMenuId, optionByDurationMenuId);
    int optionByLastCommitMenuId = toolPanel->GetOptionByLastCommitMenu()->GetId(); 
    Bind(wxEVT_MENU, &TaskListPanel::OnSortOptionSelected, this,
        optionByLastCommitMenuId, optionByLastCommitMenuId);

    int optionAscendingId = toolPanel->GetOptionAscending()->GetId();
    Bind(wxEVT_MENU, &TaskListPanel::OnOrderOptionSelected, this,
        optionAscendingId, optionAscendingId);
    int optionDescendingId = toolPanel->GetOptionDescending()->GetId();
    Bind(wxEVT_MENU, &TaskListPanel::OnOrderOptionSelected, this,
        optionDescendingId, optionDescendingId);
}

std::vector<TaskPanel*> TaskListPanel::GetAllTaskPanel() {
    std::vector<TaskPanel*> taskPanelVector;
    for(auto taskPanel : taskListWindow->GetSizer()->GetChildren()) {
        taskPanelVector.push_back(static_cast<TaskPanel*>(taskPanel->GetWindow())); 
    }
    return taskPanelVector;
}
TaskListPanel::~TaskListPanel() {
}

/*
std::vector<TRTask*> TaskListPanel::RetrieveTasks() {
    std::vector<TRTask*> taskList;
    wxSizerItemList taskListWindowChildren = taskListWindow-> 
        GetSizer()->GetChildren();
    for(auto tmp_ptr : taskListWindowChildren) {
        TaskPanel *taskPanel = (TaskPanel*) tmp_ptr;
        taskList.push_back(taskPanel->GetTask());
    }
    return taskList;
}*/
