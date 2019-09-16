#ifndef HEADER_TASK_LIST_PANEL
#define HEADER_TASK_LIST_PANEL

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif //WX_PRECOMP

#include <wx/scrolwin.h>

#include <vector>

#include "TRTask.h"
#include "TaskFileHandler.h"
#include "TaskPanel.h"
#include "TaskListToolPanel.h"
#include "BuildTaskDialog.h"

class TaskListPanel : public wxPanel {
private:
    wxScrolled<wxWindow> *taskListWindow;
    TaskHandler *taskHandler;
    TaskListToolPanel *toolPanel;
    wxTimer* taskTimer;
    void SetTimer();

    void LoadExistTask();
    void SaveTask(); ///should not be responsibility of this class
    void CreateToolMenu();
    void CreateAppearance();

    void AddExistTask(unsigned taskId);
    void AddNewTask(TRTask newTask);

    void DeleteTask(unsigned taskId); ///just delegated
    void OnClose(wxCommandEvent &event);
    //std::vector<TRTask*> RetrieveTasks();

    void FilterTask();

    void OnTimerNotify(wxTimerEvent& event);
    void OnClickAddButton(wxCommandEvent& event);
    void OnClickFocusModeCheckBox(wxCommandEvent& event);
    void OnChangeSearchBox(wxCommandEvent& event);
    void BindControl();

    void OnSortOptionSelected(wxCommandEvent &event);
    static bool TaskPanelNameComparator(const TaskPanel* p1, const TaskPanel *p2);
    static bool TaskPanelDurationComparator(const TaskPanel* p1, const TaskPanel *p2);
    static bool TaskPanelLastCommitComparator(const TaskPanel* p1, const TaskPanel *p2);
    void OnOrderOptionSelected(wxCommandEvent &event);
    std::vector<TaskPanel*> GetAllTaskPanel();
public:
    TaskListPanel(wxWindow *parent, TaskHandler *taskHandler);
    ~TaskListPanel();
};
#endif  //HEADER_TASK_LIST_PANEL
