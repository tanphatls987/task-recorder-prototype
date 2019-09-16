#include "BuildTaskDialog.h"

BuildTaskDialog::BuildTaskDialog(wxWindow *parent, TRTask* task, const std::string& frameName) 
    : wxDialog(
    parent, 
    wxID_ANY, 
    frameName, 
    wxDefaultPosition, 
    wxDefaultSize, 
    wxDEFAULT_DIALOG_STYLE | wxWS_EX_VALIDATE_RECURSIVELY) 
{
    this->task = task;
    buildTaskPanel = new BuildTaskPanel(this, task);

    SetSizer(new wxBoxSizer(wxVERTICAL));
    GetSizer()->Add(buildTaskPanel, 1, wxEXPAND, 0);
    GetSizer()->Add(CreateButtonSizer(wxOK | wxCANCEL), 0, wxALIGN_RIGHT | wxALL, 20);
    
    Fit();

    buildTaskPanel->SetValidator(BuildTaskValidator(task, buildTaskPanel));
    //assert(GetValidator() != NULL);

    //std::cerr << "Create task dialog\n";
    //Bind(wxEVT_CLOSE_WINDOW, &BuildTaskDialog::OnClose, this, GetId(), GetId());    
}

/* do I need this?*/
void BuildTaskDialog::SetExcludedNameList(std::vector<wxString> &nameList) {
    buildTaskPanel->SetExcludedNameList(nameList);
}
BuildTaskPanel* BuildTaskDialog::GetBuildTaskPanel() {
    return buildTaskPanel;
}
/*
void BuildTaskDialog::OnClose(wxCloseEvent& event) {
    GetParent()->Enable(true);
    Destroy();
}*/
