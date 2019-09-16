#include "TaskListToolPanel.h"

//TaskListToolPanel::
TaskListToolPanel::TaskListToolPanel(wxWindow *parentWindow)
    : wxPanel(parentWindow) {
    wxBitmap bitmapAdd("Images/Icons/add.png", wxBITMAP_TYPE_PNG);    
    addButton = new wxBitmapButton(this, wxID_ANY, bitmapAdd);

    taskSearchCtrl = new wxSearchCtrl(this, wxID_ANY);

    focusCtrl = new wxCheckBox(this, wxID_ANY, "Focus mode");

    menuButton = new wxButton(this, wxID_ANY, "Menu");
    int menuButtonId = menuButton->GetId();
    Bind(wxEVT_BUTTON, &TaskListToolPanel::OnClickMenuButton, this, menuButtonId, menuButtonId);

    CreateMenu();
    CreateAppearance();
}
void TaskListToolPanel::CreateAppearance() {
    wxBoxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);

    int spacing = 10;
    int itemFlag = wxRIGHT | wxALIGN_BOTTOM;
    sizer->Add(addButton, 0, itemFlag, spacing);
    sizer->Add(taskSearchCtrl, 1, itemFlag, spacing);
    sizer->Add(focusCtrl, 0, itemFlag, spacing);
    sizer->Add(menuButton, 0, wxALIGN_BOTTOM, spacing);

    SetSizer(sizer);
}

void TaskListToolPanel::CreateMenu() {
    menu = new wxMenu();
    optionByName = menu->AppendRadioItem(wxID_ANY, "Name");
    optionByLastCommit = menu->AppendRadioItem(wxID_ANY, "Last commit");
    optionByDuration = menu->AppendRadioItem(wxID_ANY, "Duration");
    menu->AppendSeparator();
    optionAscending = menu->AppendRadioItem(wxID_ANY, "Ascending");
    optionDescending = menu->AppendRadioItem(wxID_ANY, "Descending");
}
void TaskListToolPanel::OnClickMenuButton(wxCommandEvent& event) {
    PopupMenu(menu);
}
wxButton* TaskListToolPanel::GetAddButton() {
    return addButton;
}
wxMenu* TaskListToolPanel::GetMenu() {
    return menu;
}
wxSearchCtrl* TaskListToolPanel::GetTaskSearchCtrl() {
    return taskSearchCtrl;
}
wxMenuItem *TaskListToolPanel::GetOptionByNameMenu() {
    return optionByName;
}
wxMenuItem *TaskListToolPanel::GetOptionByDurationMenu() {
    return optionByDuration;
}
wxMenuItem *TaskListToolPanel::GetOptionByLastCommitMenu() {
    return optionByLastCommit;
}
wxMenuItem *TaskListToolPanel::GetOptionAscending() {
    return optionAscending;
}
wxMenuItem *TaskListToolPanel::GetOptionDescending() {
    return optionDescending;
}
wxCheckBox* TaskListToolPanel::GetFocusCtrl() {
    return focusCtrl;
}
TaskListToolPanel::~TaskListToolPanel() {
    delete(menu);
}
bool TaskListToolPanel::IsSortByNameSelected() {
    return optionByName->IsChecked(); 
}
bool TaskListToolPanel::IsSortByDurationSelected() {
    return optionByDuration->IsChecked(); 
}
bool TaskListToolPanel::IsSortByLastCommitSelected() {
    return optionByLastCommit->IsChecked(); 
}
bool TaskListToolPanel::IsAscendingSelected() {
    return optionAscending->IsChecked(); 
}
bool TaskListToolPanel::IsDescendingSelected() {
    return optionDescending->IsChecked(); 
}
