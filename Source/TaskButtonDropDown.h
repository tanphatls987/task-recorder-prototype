#ifndef HEADER_TASK_BUTTON_DROPDOWN
#define HEADER_TASK_BUTTON_DROPDOWN

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif //WX_PRECOMP


class TaskButtonDropDown : public wxPanel {
private:
    wxBitmapButton* timerPlayButton;
    wxBitmapButton* timerPauseButton;
    wxBitmapButton* timerStopButton;
    wxBitmapButton* timerEraseButton;
    wxTextCtrl* timerDisplayBox;
    wxMenu* dropDownTaskMenu;
    wxBitmapButton* taskMenuButton;

    wxMenuItem* menuQuickAdd;
    wxMenuItem* menuQuickCommit;
    wxMenuItem* menuAdd;
    wxMenuItem* menuCommit;
    wxMenuItem* menuModify;
    wxMenuItem* menuDelete;
    void CreateAppearance();

public: 
    TaskButtonDropDown(wxWindow *parent);
    ~TaskButtonDropDown();

    wxMenu* GetDropDownTaskMenu();
    wxBitmapButton* GetTimerPlayButton();
    wxBitmapButton* GetTimerPauseButton();
    wxBitmapButton* GetTimerStopButton();
    wxBitmapButton* GetTimerEraseButton();
    wxBitmapButton* GetTaskMenuButton();
    wxTextCtrl* GetTimerDisplayBox();
    void SetDropDownTaskMenu(wxMenu *menu);
    void SetTimerPlayButton(wxBitmapButton *button);
    void SetTimerPauseButton(wxBitmapButton *button);
    void SetTimerStopButton(wxBitmapButton *button);
    void SetTimerEraseButton(wxBitmapButton *button);
    void SetTimerDisplayBox(wxTextCtrl *textCtrl);
    wxMenuItem* GetMenuQuickAdd();
    wxMenuItem* GetMenuQuickCommit();
    wxMenuItem* GetMenuAdd();
    wxMenuItem* GetMenuCommit();
    wxMenuItem* GetMenuDelete();
    wxMenuItem* GetMenuModify();

    void OnClickTaskMenuButton(wxCommandEvent &event);
    void SetTimerDisplayValue(std::string time);
};
#endif //HEADER_TASK_BUTTON_DROPDOWN
