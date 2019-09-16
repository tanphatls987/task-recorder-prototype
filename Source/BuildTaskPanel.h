#ifndef HEADER_BUILD_TASK_PANEL
#define HEADER_BUILD_TASK_PANEL

#include <string>
#include <ctime>
#include <vector>

#include <wx/datectrl.h>
#include <wx/timectrl.h>
#include <wx/wxprec.h>
#include <wx/spinctrl.h>
#include <wx/arrstr.h>

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif //WX_PRECOMP

#include "TRTask.h"

class BuildTaskPanel : public wxPanel { ///reusable for modified
private: 
    TRTask* task;

    wxTextCtrl* nameBox; ///always have 
    wxPanel* namePanel;

    wxCheckBox* dateTimeCheckBox; ///these are begging me to create new class, is it necessary?
    wxPanel* dateTimePanel; ///these panel is to disable the whole thing in one command
    wxDatePickerCtrl* datePicker;
    wxTimePickerCtrl* timePicker;

    wxCheckBox* countCheckBox;
    wxPanel* countPanel;
    wxSpinCtrl* countPicker;

    wxCheckBox* durationCheckBox;
    wxPanel* durationPanel;
    wxSpinCtrl* durationDayPicker;
    wxTimePickerCtrl* durationTimePicker;

    wxPanel* buttonPanel;
    wxButton* buttonOk;
    wxButton* buttonCancel;

    void LoadTask();

    void CreateDateTimePicker();
    void CreateDateTimePanel();
    void CreateNamePanel();
    void CreateCountPanel();
    void CreateDurationPanel();
    void CreateButtonPanel();
    void CreateAppearance();

    void OnCancel(wxCommandEvent& event);
    void OnOk(wxCommandEvent& event);
    void OnClose(wxCloseEvent& event);

    void OnClickDateTimeCheckBox(wxCommandEvent& event);
    void OnClickCountCheckBox(wxCommandEvent& event);
    void OnClickDurationCheckBox(wxCommandEvent& event);

    void BindControl();
public:
    BuildTaskPanel(wxWindow* parent, TRTask* task);
    void SetExcludedNameList(std::vector<wxString> &nameList);
    TRTask* GetTask();
    bool Validate() override;
};

#endif //HEADER_BUILD_TASK_PANEL

