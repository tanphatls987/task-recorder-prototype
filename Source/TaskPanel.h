#ifndef HEADER_TASK_PANEL
#define HEADER_TASK_PANEL

#include <sstream>
#include <iomanip>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif //WX_PRECOMP

#include "TRTask.h"
#include "TaskButtonDropDown.h"
#include "TaskHandler.h"



class TaskPanel : public wxPanel {
private:
    TaskHandler *taskHandler;
    unsigned taskId;
    wxButton *taskButton;
    TaskButtonDropDown* dropDown;

    //and now I don't even need to store the sizer
    wxBoxSizer *MakeSizer(); ///you know what, I can stuff the sizer of dropDown inside this sizer to make life easier

    wxString GetTaskInfo();
    void OnClickAddMenu(wxCommandEvent &event);
    void OnClickQuickAddMenu(wxCommandEvent &event);

    void OnClickCommitMenu(wxCommandEvent &event);
    void OnClickQuickCommitMenu(wxCommandEvent &event);

    void OnClickModifyMenu(wxCommandEvent &event);
    void OnClickDeleteMenu(wxCommandEvent &event);


    void OnClickPlayButton(wxCommandEvent &event);
    void OnClickPauseButton(wxCommandEvent &event);
    void OnClickStopButton(wxCommandEvent &event);
    void OnClickEraseButton(wxCommandEvent &event);
    void OnClickTaskButton(wxCommandEvent &event); 
    void OnUpdate();

    void BindControl();

    std::string GetDisplayTime(int time);
public: 
    TaskPanel(wxWindow *parent, TaskHandler* taskHandler, unsigned taskId);
    ~TaskPanel();


    //bypass 
    TRTask* GetTask() const;
    bool IsValid();
    bool IsDisplayable(bool focusMode, std::string prefix);

    //int GetRunningTime(time_t currentTime = time(NULL)); ///why it is here?
    void UpdateRunningTime(time_t currentTime = time(NULL));
    void UpdateTaskName(const std::string &name);
};
#endif //HEADER_TASK_PANEL

