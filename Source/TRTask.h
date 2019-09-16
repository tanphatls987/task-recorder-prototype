#ifndef HEADER_FILE_TRTASK
#define HEADER_FILE_TRTASK

#include <time.h>
#include <cstring>
#include <chrono>

#include <wx/wxprec.h>
#ifndef WX_PRECOMP
    #include <wx/wx.h>
#endif //WX_PRECOMP

/*
 * Right now the code isn't support unicode yet.
 */

class TRTask {
private:
    static const int NAME_LENGTH_LIMIT = 200;
    std::string taskName;    
    time_t lastDone; //according to documentation, will be -1 for invalid date
    unsigned timeDone;
    long long timeElapsed; //in s, won't be accurate to ms but who care? Also left it as long long for fun
    time_t recordingStartTime;

    long long recordingStoredTime; ///to add when there is pausing
    TRTask* backUpTask; ///only available when record task to reverse the changed if necessary

    enum TaskState {recording, pausing, idle}; 
    TaskState state;

    bool displayTimeDone;
    bool displayLastDone;
    bool displayTimeElapsed;



    void Recover();
public:
    void Make(std::string desc); ///for loading from text file

    ///handling construction and assignment
    TRTask(std::string taskName = "", time_t lastDone = time(NULL), unsigned timeDone = 0, int timeElapsed = 0);
    TRTask(const TRTask& oth);
    TRTask& operator = (const TRTask& oth);
    

    unsigned GetTimeDone(bool realValue = false);
    bool AddTimeDone(unsigned time = 1);
    void SetTimeDone(unsigned time = 0);

    time_t GetLastDone(bool realValue = false);
    tm GetLastDoneTm() const;
    void SetLastDone(time_t timeStamp = -1);
    bool IsLastDoneValid() const;

    //Function for taskName handling
    void SetName(std::string name);
    std::string GetName() const;
    bool IsNameEqual(const TRTask& oth);
    bool HavePrefix(const std::string &prefix); 
    static int GetMaxNameLength();

    //misc for task handling
    void QuickCommit();
    void Commit(time_t timeStamp = time(NULL));
    void ResetCounter();
    
    ///for time elapsed
    long long GetTimeElapsed(bool realValue = false);
    void SetTimeElapsed(long long timeElapsed = 0);
    void AddTimeElapsed(long long timeAdd);

    int GetRecordingTime(time_t currentTime = time(NULL));

    bool StartRecord();
    bool PauseRecord();
    bool UnpauseRecord();
    bool StopRecord(bool isValid = false);

    bool IsActive();
    bool IsIdle();
    bool IsRecording();
    bool IsPausing();


    void SetDisplayTimeDone(bool display);
    void SetDisplayLastDone(bool display);
    void SetDisplayTimeElapsed(bool display);

    bool GetDisplayTimeDone();
    bool GetDisplayLastDone();
    bool GetDisplayTimeElapsed();
    ///this is used for file input/output
    std::string ToString();
};

#endif //HEADER_FILE_TRTASK
