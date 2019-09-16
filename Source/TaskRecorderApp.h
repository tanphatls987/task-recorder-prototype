#ifndef HEADER_TASKGIVERAPP
#define HEADER_TASKGIVERAPP

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif //WX_PRECOMP

#include "TaskRecorderMainFrame.h"

class TaskRecorderApp : public wxApp {
public: 
    ~TaskRecorderApp();
    virtual bool OnInit();
};
#endif //HEADER_TASKGIVERAPP
