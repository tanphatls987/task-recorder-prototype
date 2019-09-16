#include "TaskButtonDropDown.h"


TaskButtonDropDown::TaskButtonDropDown(wxWindow *parent) :
    wxPanel(parent, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxTAB_TRAVERSAL | wxBORDER_SUNKEN) {
    /*
     * Create all component.
     */

    wxBitmap bitmapPlay("Images/Icons/play.png", wxBITMAP_TYPE_PNG);
    timerPlayButton = new wxBitmapButton(this, wxID_ANY, bitmapPlay);

    wxBitmap bitmapPause("Images/Icons/pause.png", wxBITMAP_TYPE_PNG);
    timerPauseButton = new wxBitmapButton(this, wxID_ANY, bitmapPause);
    
    wxBitmap bitmapStop("Images/Icons/stop.png", wxBITMAP_TYPE_PNG);
    timerStopButton = new wxBitmapButton(this, wxID_ANY, bitmapStop);

    wxBitmap bitmapErase("Images/Icons/bin-3.png", wxBITMAP_TYPE_PNG);
    timerEraseButton = new wxBitmapButton(this, wxID_ANY, bitmapErase);

    wxBitmap bitmapMenu("Images/Icons/menu.png", wxBITMAP_TYPE_PNG);
    taskMenuButton = new wxBitmapButton(this, wxID_ANY, bitmapMenu);

    int taskMenuButtonId = taskMenuButton->GetId();
    Bind(wxEVT_BUTTON, &TaskButtonDropDown::OnClickTaskMenuButton, this, taskMenuButtonId, taskMenuButtonId);

    timerDisplayBox = new wxTextCtrl(this, wxID_ANY, "0s");  
    timerDisplayBox->SetEditable(false);
    
    dropDownTaskMenu = new wxMenu();

    menuQuickAdd = dropDownTaskMenu->Append(wxID_ANY, "Quick add");
    menuQuickCommit = dropDownTaskMenu->Append(wxID_ANY, "Quick commit");

    dropDownTaskMenu->AppendSeparator();
    menuAdd = dropDownTaskMenu->Append(wxID_ANY, "Add");
    menuCommit = dropDownTaskMenu->Append(wxID_ANY, "Commit");
    menuModify = dropDownTaskMenu->Append(wxID_ANY, "Modify");
    menuDelete = dropDownTaskMenu->Append(wxID_ANY, "Delete");
    CreateAppearance();
}
void TaskButtonDropDown::CreateAppearance() {
    int spacing = 5;
    wxBoxSizer* dropDownSizer = new wxBoxSizer(wxHORIZONTAL);
    //std::cerr << "Add widgets\n";
    dropDownSizer->Add(timerPlayButton, 0, wxALL, spacing);
    dropDownSizer->Add(timerPauseButton, 0, wxALL, spacing);
    dropDownSizer->Add(timerStopButton, 0, wxALL, spacing);
    dropDownSizer->AddSpacer(10);
    dropDownSizer->Add(timerDisplayBox, 0, wxALL, spacing);
    dropDownSizer->Add(timerEraseButton, 0, wxALL, spacing);
    dropDownSizer->Add(taskMenuButton, 0, wxALL, spacing);
    SetSizer(dropDownSizer);
}



wxMenu* TaskButtonDropDown::GetDropDownTaskMenu() {
    return dropDownTaskMenu;
}
wxBitmapButton* TaskButtonDropDown::GetTimerPlayButton() {
    return timerPlayButton;
}
wxBitmapButton* TaskButtonDropDown::GetTimerPauseButton() {
    return timerPauseButton;
}
wxBitmapButton* TaskButtonDropDown::GetTimerStopButton() {
    return timerStopButton;
}
wxBitmapButton* TaskButtonDropDown::GetTimerEraseButton() {
    return timerEraseButton;
}
wxBitmapButton* TaskButtonDropDown::GetTaskMenuButton() {
    return taskMenuButton;
}
wxTextCtrl* TaskButtonDropDown::GetTimerDisplayBox() {
    return timerDisplayBox;
}
void TaskButtonDropDown::SetDropDownTaskMenu(wxMenu *menu) {
    dropDownTaskMenu = menu;
}
void TaskButtonDropDown::SetTimerPlayButton(wxBitmapButton *button) {
    timerPlayButton = button;
}
void TaskButtonDropDown::SetTimerPauseButton(wxBitmapButton *button) {
    timerPauseButton = button;
}
void TaskButtonDropDown::SetTimerStopButton(wxBitmapButton *button) {
    timerStopButton = button;
}
void TaskButtonDropDown::SetTimerEraseButton(wxBitmapButton *button) {
    timerEraseButton = button;
}
void TaskButtonDropDown::SetTimerDisplayBox(wxTextCtrl *textCtrl){
    timerDisplayBox = textCtrl; 
}
wxMenuItem* TaskButtonDropDown::GetMenuQuickAdd(){
    return menuQuickAdd;    
}
wxMenuItem* TaskButtonDropDown::GetMenuQuickCommit(){
    return menuQuickCommit;
}
wxMenuItem* TaskButtonDropDown::GetMenuAdd(){
    return menuAdd;
}
wxMenuItem* TaskButtonDropDown::GetMenuCommit(){
    return menuCommit;
}
wxMenuItem* TaskButtonDropDown::GetMenuDelete(){
    return menuDelete;
}
wxMenuItem* TaskButtonDropDown::GetMenuModify(){
    return menuModify;
}
void TaskButtonDropDown::OnClickTaskMenuButton(wxCommandEvent &event) {
    PopupMenu(dropDownTaskMenu);
}


void TaskButtonDropDown::SetTimerDisplayValue(std::string time) {
    timerDisplayBox->SetValue(time);
}
TaskButtonDropDown::~TaskButtonDropDown() {
    //others was handled by wxWidget
    //std::cerr << "Dropdown destroy\n";
    delete(dropDownTaskMenu); /// pop up menu is delete later
}
