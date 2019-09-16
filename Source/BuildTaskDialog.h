#ifndef HEADER_BUILD_TASK_DIALOG
#define HEADER_BUILD_TASK_DIALOG

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif //WX_PRECOMP

#include "BuildTaskPanel.h"
#include "BuildTaskValidator.h"

class BuildTaskDialog : public wxDialog {
private:
    TRTask* task;
    BuildTaskPanel* buildTaskPanel;
    std::vector<std::string> banName;
    //void OnClose(wxCloseEvent& event);
public:
    BuildTaskDialog(wxWindow *parent, TRTask* task, const std::string& frameName);
    void SetExcludedNameList(std::vector<wxString> &nameList);
    BuildTaskPanel* GetBuildTaskPanel();
};

#endif //HEADER_BUILD_TASK_DIALOG
