#include "BuildTaskValidator.h"

///BuildTaskValidator::
BuildTaskValidator::BuildTaskValidator(TRTask *task, BuildTaskPanel *buildTaskPanel) :
    wxValidator() {
    this->task = task;
    this->buildTaskPanel = buildTaskPanel;
}
wxObject* BuildTaskValidator::Clone() const {
    return new BuildTaskValidator(task, buildTaskPanel);
}

bool BuildTaskValidator::TransferFromWindow() {
    //std::cerr << "Call build validator\n";
    return true;
}
bool BuildTaskValidator::TransferToWindow() {
    //std::cerr << "Call build validator\n";
    return true;    
}
bool BuildTaskValidator::Validate(wxWindow* parent) {
    //std::cerr << "Validator invoked\n";
    return buildTaskPanel->Validate();
}
