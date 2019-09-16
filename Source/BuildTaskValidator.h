#ifndef HEADER_BUILD_TASK_VALIDATOR
#define HEADER_BUILD_TASK_VALIDATOR

#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif //WX_PRECOMP

#include <wx/validate.h>

#include "TRTask.h"
#include "BuildTaskPanel.h"

/*
 * This file right now have only 1 usage : to pull the data from dialog back to the task when done
 */
class BuildTaskValidator : public wxValidator {
private:
    TRTask *task;
    BuildTaskPanel *buildTaskPanel;
public:
    BuildTaskValidator(TRTask *task, BuildTaskPanel *buildTaskPanel);
    virtual wxObject* Clone() const override;
    virtual bool TransferFromWindow () override; 
    virtual bool TransferToWindow() override;
    virtual bool Validate(wxWindow *parent) override;
};
#endif //HEADER_BUILD_TASK_VALIDATOR
