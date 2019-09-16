#ifndef HEADER_FILE_TASK_LIST_TOOL_PANEL
#define HEADER_FILE_TASK_LIST_TOOL_PANEL

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif //WX_PRECOMP

#include <wx/srchctrl.h>

class TaskListToolPanel : public wxPanel{
private:
    wxBitmapButton* addButton;
    wxSearchCtrl* taskSearchCtrl;
    wxButton* menuButton;
    wxMenu* menu;
    wxCheckBox* focusCtrl;

    wxMenuItem *optionByName;
    wxMenuItem *optionByLastCommit;
    wxMenuItem *optionByDuration;

    wxMenuItem *optionAscending;
    wxMenuItem *optionDescending;

    void CreateMenu();
    void CreateAppearance();
    void OnClickMenuButton(wxCommandEvent& event);
public:
    TaskListToolPanel(wxWindow *parentWindow);
    ~TaskListToolPanel();

    wxButton* GetAddButton();
    wxMenu* GetMenu();
    wxSearchCtrl* GetTaskSearchCtrl();
    wxCheckBox* GetFocusCtrl();


    wxMenuItem *GetOptionByNameMenu();
    wxMenuItem *GetOptionByDurationMenu();
    wxMenuItem *GetOptionByLastCommitMenu();

    wxMenuItem *GetOptionAscending();
    wxMenuItem *GetOptionDescending();


    bool IsSortByNameSelected();
    bool IsSortByDurationSelected();
    bool IsSortByLastCommitSelected();

    bool IsAscendingSelected();
    bool IsDescendingSelected();
};

#endif // HEADER_FILE_TASK_LIST_TOOL_PANEL
