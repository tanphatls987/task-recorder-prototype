#include "BuildTaskPanel.h"

BuildTaskPanel::BuildTaskPanel(
    wxWindow* parent, 
    TRTask* task
) 
    : wxPanel(parent, wxID_ANY) {
    this->task = task;
    CreateNamePanel();
    CreateDateTimePanel();
    CreateCountPanel();
    CreateDurationPanel();
    //CreateButtonPanel();
    BindControl();

    CreateAppearance();
    LoadTask();
}

TRTask* BuildTaskPanel::GetTask() {
    ///this should only be called when the task is already valid

    std::string taskName = nameBox->GetValue().ToStdString();
    task->SetName(taskName);

    if (dateTimeCheckBox->IsChecked()) {
        task->SetDisplayLastDone(true);
        wxDateTime dayPart = datePicker->GetValue();
        wxDateTime timePart = timePicker->GetValue();
        dayPart.SetHour(timePart.GetHour());
        dayPart.SetMinute(timePart.GetMinute());
        dayPart.SetSecond(timePart.GetSecond());
        task->SetLastDone(dayPart.GetTicks());
    } else {
        task->SetDisplayLastDone(false);
        task->SetLastDone();
    }
    
    if (countCheckBox->IsChecked()) {
        int count = countPicker->GetValue();
        task->SetTimeDone(count);
        task->SetDisplayTimeDone(true);
    } else {
        task->SetTimeDone();
        task->SetDisplayTimeDone(false);
    }
    
    if (durationCheckBox->IsChecked()) {
        wxDateTime durationSmall = durationTimePicker->GetValue();
        long long durationDay = durationDayPicker->GetValue();
        long long duration = (durationSmall - durationSmall.GetDateOnly()).GetSeconds().ToLong() + durationDay * 24 * 60 * 60;
        task->SetTimeElapsed(duration);
        task->SetDisplayTimeElapsed(true);
    } else {
        task->SetTimeElapsed(0);
        task->SetDisplayTimeElapsed(false);
    }
    
    return task;
}

void BuildTaskPanel::SetExcludedNameList(std::vector<wxString> &nameList) {
    //std::cerr << "Call excluded name list\n";
    wxTextValidator* nameValidator = (wxTextValidator*) nameBox->GetValidator();
    wxArrayString arrNameList;
    for(auto i : nameList)
        arrNameList.Add(i);
    //std::cerr << "End excluded name list\n";
    nameValidator->SetExcludes(arrNameList); 
    //std::cerr << "End excluded name list\n";
}

void BuildTaskPanel::CreateDateTimePicker() {
    int itemBorder = 20;
    int spacerSize = 5;
    int itemDefaultFlag = wxLEFT | wxRIGHT | wxEXPAND;
    wxSizer* datePickerSizer = new wxBoxSizer(wxVERTICAL);
    datePicker = new wxDatePickerCtrl(dateTimePanel, wxID_ANY);  

    tm dateLowerBound = {0, 0, 0, 1, 0, 1990 - 1900};
    tm dateUpperBound = {59, 59, 23, 1, 0, 2030 - 1900};
    datePicker->SetRange(wxDateTime(dateLowerBound), wxDateTime(dateUpperBound));

    wxStaticText* tagDate = new wxStaticText(
        dateTimePanel, 
        -1, 
        wxString("Date"), 
        wxDefaultPosition, 
        wxDefaultSize, 
        wxALIGN_LEFT
    );


    datePickerSizer->AddSpacer(spacerSize);
    datePickerSizer->Add(tagDate, 0, itemDefaultFlag, itemBorder);  
    datePickerSizer->AddSpacer(spacerSize);
    datePickerSizer->Add(datePicker, 0, itemDefaultFlag, itemBorder);
    datePickerSizer->AddSpacer(spacerSize);

    wxSizer* timePickerSizer = new wxBoxSizer(wxVERTICAL);
    timePicker = new wxTimePickerCtrl(dateTimePanel, wxID_ANY);

    wxStaticText* tagTime = new wxStaticText(
        dateTimePanel, 
        -1, 
        wxString("Time"), 
        wxDefaultPosition, 
        wxDefaultSize, 
        wxALIGN_LEFT
    );


    timePickerSizer->AddSpacer(spacerSize);
    timePickerSizer->Add(tagTime, 0, itemDefaultFlag, itemBorder);  
    timePickerSizer->AddSpacer(spacerSize);
    timePickerSizer->Add(timePicker, 0, itemDefaultFlag, itemBorder);
    timePickerSizer->AddSpacer(spacerSize);
}
void BuildTaskPanel::CreateDateTimePanel() {
    dateTimePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE); 
    wxSizer *sizer = new wxBoxSizer(wxHORIZONTAL);
    dateTimePanel->SetSizer(sizer);
    dateTimeCheckBox = new wxCheckBox(this, wxID_ANY, "Last commit date time");

    CreateDateTimePicker();

    int itemBorder = 20;
    int spacerSize = 5;
    int itemDefaultFlag = wxALL | wxALIGN_CENTER;

    
    sizer->Add(datePicker->GetContainingSizer(), 1, itemDefaultFlag, itemBorder);
    sizer->AddSpacer(spacerSize);
    sizer->Add(timePicker->GetContainingSizer(), 1, itemDefaultFlag, itemBorder);
}
void BuildTaskPanel::CreateCountPanel() {
    countCheckBox = new wxCheckBox(this, wxID_ANY, "Commit time record");
    countPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE); 
    countPicker = new wxSpinCtrl(countPanel, wxID_ANY);

    wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    countPanel->SetSizer(sizer);

    wxStaticText* tagCount = new wxStaticText(
        countPanel, 
        -1, 
        wxString("Time commit"), 
        wxDefaultPosition, 
        wxDefaultSize, 
        wxALIGN_LEFT
    );
    int itemBorder = 20;
    int spacerSize = 5;
    int itemDefaultFlag = wxLEFT | wxRIGHT | wxEXPAND;
    sizer->AddSpacer(spacerSize);
    sizer->Add(tagCount, 0, itemDefaultFlag, itemBorder);
    sizer->AddSpacer(spacerSize);
    sizer->Add(countPicker, 0, itemDefaultFlag, itemBorder);
    sizer->AddSpacer(spacerSize + 10);

}
void BuildTaskPanel::CreateDurationPanel() {
    durationCheckBox = new wxCheckBox(this, wxID_ANY, "Duration");
    durationPanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE); 
    durationDayPicker = new wxSpinCtrl(durationPanel, wxID_ANY);
    durationTimePicker = new wxTimePickerCtrl(durationPanel, wxID_ANY); 

    wxSizer *dayTimeSizer = new wxBoxSizer(wxHORIZONTAL);
    dayTimeSizer->Add(durationDayPicker, 0, wxRIGHT | wxALIGN_BOTTOM | wxEXPAND, 3); 
    dayTimeSizer->Add(new wxStaticText(durationPanel, -1, "day(s)"), 0, wxRIGHT | wxALIGN_BOTTOM, 5);
    dayTimeSizer->Add(durationTimePicker, 0, wxEXPAND | wxALIGN_BOTTOM);

    wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    durationPanel->SetSizer(sizer);

    wxStaticText* tagDuration = new wxStaticText(
        durationPanel, 
        -1, 
        wxString("Duration"), 
        wxDefaultPosition, 
        wxDefaultSize, 
        wxALIGN_LEFT
    );
    int itemBorder = 20;
    int spacerSize = 5;
    int itemDefaultFlag = wxLEFT | wxRIGHT | wxEXPAND;
    sizer->AddSpacer(spacerSize);
    sizer->Add(tagDuration, 0, itemDefaultFlag, itemBorder);
    sizer->AddSpacer(spacerSize);
    sizer->Add(dayTimeSizer, 0, itemDefaultFlag, itemBorder);
    sizer->AddSpacer(spacerSize + 10);

}
void BuildTaskPanel::CreateNamePanel() {
    namePanel = new wxPanel(this, wxID_ANY, wxDefaultPosition, wxDefaultSize, wxBORDER_SIMPLE); 
    nameBox = new wxTextCtrl(namePanel, wxID_ANY);
    nameBox->SetMaxLength(TRTask::GetMaxNameLength());

    wxTextValidator nameValidator = wxTextValidator(
        wxFILTER_EMPTY | wxFILTER_EXCLUDE_LIST);
    nameBox->SetValidator(nameValidator);

    //assert(nameBox->GetValidator() != NULL);


    wxSizer *sizer = new wxBoxSizer(wxVERTICAL);
    namePanel->SetSizer(sizer);

    wxStaticText* tagName = new wxStaticText(
        namePanel, 
        -1, 
        wxString("Name"), 
        wxDefaultPosition, 
        wxDefaultSize, 
        wxALIGN_LEFT
    );
    int itemBorder = 20;
    int spacerSize = 5;
    int itemDefaultFlag = wxLEFT | wxRIGHT | wxEXPAND;
    sizer->AddSpacer(spacerSize);
    sizer->Add(tagName, 0, itemDefaultFlag, itemBorder);
    sizer->AddSpacer(spacerSize);
    sizer->Add(nameBox, 0, itemDefaultFlag, itemBorder);
    sizer->AddSpacer(spacerSize);
}
//void BuildTaskPanel::
void BuildTaskPanel::CreateButtonPanel() {
    buttonPanel = new wxPanel(this, wxID_ANY); 
    buttonOk = new wxButton(buttonPanel, wxID_ANY, "&OK");
    buttonCancel = new wxButton(buttonPanel, wxID_ANY, "&Cancel");

    wxSizer* sizer = new wxBoxSizer(wxHORIZONTAL);
    buttonPanel->SetSizer(sizer);
    sizer->Add(buttonCancel, 0, wxRIGHT, 5);
    sizer->Add(buttonOk, 0, 0, 0);
}
void BuildTaskPanel::CreateAppearance() {
    wxSizer* sizer = new wxBoxSizer(wxVERTICAL);
    this->SetSizer(sizer);
    int spacerSize = 5;

    int itemBorder = 30;
    int itemDefaultFlag = wxLEFT | wxRIGHT | wxEXPAND | wxALIGN_CENTER;

    int checkBoxBorder = 15;
    int checkBoxDefaultFlag = wxLEFT | wxRIGHT;

    sizer->AddSpacer(30);
    sizer->Add(namePanel, 0, itemDefaultFlag, itemBorder);
    sizer->AddSpacer(spacerSize);

    sizer->Add(dateTimeCheckBox, 0, checkBoxDefaultFlag, checkBoxBorder);
    sizer->Add(dateTimePanel, 0, itemDefaultFlag, itemBorder);
    sizer->AddSpacer(spacerSize);
   
    sizer->Add(countCheckBox, 0, checkBoxDefaultFlag, checkBoxBorder);
    sizer->Add(countPanel, 0, itemDefaultFlag, itemBorder);
    sizer->AddSpacer(spacerSize);
   
    sizer->Add(durationCheckBox, 0, checkBoxDefaultFlag, checkBoxBorder);
    sizer->Add(durationPanel, 0, itemDefaultFlag, itemBorder);
    sizer->AddSpacer(spacerSize);
    sizer->AddSpacer(20);
    /*
    sizer->Add(buttonPanel, 0, wxLEFT | wxRIGHT | wxALIGN_RIGHT, itemBorder); 
    sizer->AddSpacer(10);
    */
}
void BuildTaskPanel::LoadTask() {
    nameBox->SetValue(task->GetName());
    countPicker->SetValue(task->GetTimeDone());
    tm currentTime = task->GetLastDoneTm();

    datePicker->SetValue(wxDateTime(currentTime));
    timePicker->SetValue(wxDateTime(currentTime));

    long long duration = task->GetTimeElapsed();

    long long durationDay = duration / (24 * 60 * 60);

    int durationMin = duration / 60 % 60;

    int durationHr = duration / (60 * 60) % 24;

    int durationSec = duration % 60;
    
    durationDayPicker->SetValue(durationDay);
    durationTimePicker->SetTime(durationHr, durationMin, durationSec);

    dateTimeCheckBox->SetValue(task->GetDisplayLastDone());
    durationCheckBox->SetValue(task->GetDisplayTimeElapsed());
    countCheckBox->SetValue(task->GetDisplayTimeDone());

    dateTimePanel->Enable(dateTimeCheckBox->GetValue());
    countPanel->Enable(countCheckBox->GetValue());
    durationPanel->Enable(durationCheckBox->GetValue());
}

void BuildTaskPanel::OnClickDateTimeCheckBox(wxCommandEvent& event) {
    dateTimePanel->Enable(event.IsChecked());
}
void BuildTaskPanel::OnClickCountCheckBox(wxCommandEvent& event) {
    countPanel->Enable(event.IsChecked());
}
void BuildTaskPanel::OnClickDurationCheckBox(wxCommandEvent& event) {
    durationPanel->Enable(event.IsChecked());
}
/*
void BuildTaskPanel::OnOk(wxCommandEvent& event) {
    ///some checking
    GetParent()->Close(true);
}
void BuildTaskPanel::OnCancel(wxCommandEvent& event) {
    ///maybe emit a modified box?
    GetParent()->Close(true);
}*/
void BuildTaskPanel::OnClose(wxCloseEvent& event) {
}
void BuildTaskPanel::BindControl() {
    int dateTimeCheckBoxId = dateTimeCheckBox->GetId();
    Bind(wxEVT_CHECKBOX, &BuildTaskPanel::OnClickDateTimeCheckBox, this, 
        dateTimeCheckBoxId, dateTimeCheckBoxId);
    int countCheckBoxId = countCheckBox->GetId();
    Bind(wxEVT_CHECKBOX, &BuildTaskPanel::OnClickCountCheckBox, this, 
        countCheckBoxId, countCheckBoxId);
    int durationCheckBoxId = durationCheckBox->GetId();
    Bind(wxEVT_CHECKBOX, &BuildTaskPanel::OnClickDurationCheckBox, this, 
        durationCheckBoxId, durationCheckBoxId);

    /*
    int buttonOkId = buttonOk->GetId();
    Bind(wxEVT_BUTTON, &BuildTaskPanel::OnOk, this, 
        buttonOkId, buttonOkId);
    int buttonCancelId = buttonCancel->GetId();
    Bind(wxEVT_BUTTON, &BuildTaskPanel::OnCancel, this, 
        buttonCancelId, buttonCancelId);
    */
}
bool BuildTaskPanel::Validate() {
    if (namePanel->Validate()) {
        GetTask();
        return true;
    }
    return false;
}

