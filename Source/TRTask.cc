#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <iostream>
#include <cassert>

#include "TRTask.h"

TRTask::TRTask(std::string taskName, time_t lastDone, unsigned timeDone, int timeElapsed) {
    this->taskName = taskName;
    this->lastDone = lastDone;
    this->timeDone = timeDone;
    this->timeElapsed = 0;
    this->state = idle;
    recordingStartTime = -1;
    recordingStoredTime = 0;
    
    backUpTask = NULL;
    displayTimeDone = true;
    displayLastDone = true;
    displayTimeElapsed = true;
}
TRTask::TRTask(const TRTask& oth) {
    taskName = oth.taskName;
    lastDone = oth.lastDone;
    timeDone = oth.timeDone;
    timeElapsed = oth.timeElapsed;
    recordingStartTime = oth.recordingStartTime;
    recordingStoredTime = oth.recordingStoredTime;
    state = oth.state;
    displayTimeDone = oth.displayTimeDone;
    displayLastDone = oth.displayLastDone;
    displayTimeElapsed = oth.displayTimeElapsed;

    if (oth.backUpTask != NULL) {
        backUpTask = new TRTask(*oth.backUpTask);
    } else backUpTask = NULL;
}
TRTask& TRTask::operator = (const TRTask &oth) {
    if (this != &oth) {
        taskName = oth.taskName;
        lastDone = oth.lastDone;
        timeDone = oth.timeDone;
        timeElapsed = oth.timeElapsed;
        state = oth.state;
        recordingStartTime = oth.recordingStartTime;
        recordingStoredTime = oth.recordingStoredTime;
        displayTimeDone = oth.displayTimeDone;
        displayLastDone = oth.displayLastDone;
        displayTimeElapsed = oth.displayTimeElapsed;
        if (oth.backUpTask != NULL) {
            backUpTask = new TRTask(*oth.backUpTask);
        } else backUpTask = NULL;
    }
    return *this;
}

bool TRTask::AddTimeDone(unsigned time) {
/*
 * Does not catch overflow
 */
    timeDone += time;
    return true;
}

int TRTask::GetMaxNameLength() {
    return NAME_LENGTH_LIMIT;
}
unsigned TRTask::GetTimeDone(bool realValue) {
    if (!GetDisplayTimeDone() && !realValue) return 0;
    return timeDone;
}
void TRTask::SetTimeDone(unsigned time){
    timeDone = time;
}
void TRTask::SetName(std::string name) {
    assert(name.length() < NAME_LENGTH_LIMIT);
    taskName = name;
}
std::string TRTask::GetName() const{
    return taskName;
}
bool TRTask::IsNameEqual(const TRTask& oth) {
    return GetName() == oth.GetName();
}
bool TRTask::HavePrefix(const std::string &prefix) {
    if (prefix.length() > taskName.length()) return 0;
    ///since not many task have same prefix then this should be relatively fast
    for(int i = 0; i < prefix.length(); i++) {
        if (prefix[i] != taskName[i]) return 0;
    }
    return 1;
}


void TRTask::QuickCommit() {
    Commit();
}
void TRTask::Commit(time_t timeStamp) {
    SetLastDone(timeStamp);
    timeDone++;
}
time_t TRTask::GetLastDone(bool realValue) {
    /*
     * Will not catch invalid time. 
     */
    if (!GetDisplayLastDone() && !realValue) return 0;
    return lastDone;
}
tm TRTask::GetLastDoneTm() const {
    return *localtime(&lastDone);
}
void TRTask::SetLastDone(time_t timeStamp) {
    lastDone = timeStamp; 
}
bool TRTask::IsLastDoneValid() const {
    return lastDone != -1;
}
void TRTask::ResetCounter() {
    ///the last timestamp will be kept
    SetTimeDone(0);
}

void TRTask::Make(std::string desc) {
    std::stringstream input(desc, std::ios_base::in);    
    getline(input, taskName);
    input >> lastDone >> timeDone >> timeElapsed;
}
long long TRTask::GetTimeElapsed(bool realValue) {
    if (!GetDisplayTimeElapsed() && !realValue) return 0;
    return timeElapsed;
}
void TRTask::SetTimeElapsed(long long timeElapsed) {
    this->timeElapsed = timeElapsed;
}
void TRTask::AddTimeElapsed(long long timeAdd) {
    timeElapsed += timeAdd;
}
int TRTask::GetRecordingTime(time_t currentTime) {
    assert(recordingStartTime != -1 && currentTime != -1);
    return int(difftime(currentTime, recordingStartTime)) + recordingStoredTime; 
}
bool TRTask::IsActive() {
    return state != idle;  
}

bool TRTask::StartRecord() {
    if (IsActive()) return 0;
    backUpTask = new TRTask(*this);

    recordingStartTime = time(NULL);
    recordingStoredTime = 0; //actually this line is redundant


    SetLastDone(recordingStartTime); 
    AddTimeDone(1);


    state = recording;
    return 1;
}
bool TRTask::PauseRecord() {
    if (!IsActive()) return 0;
    time_t recordingEndTime = time(NULL);
    recordingStoredTime += int(difftime(recordingEndTime, recordingStartTime));

    recordingStartTime = -1;
    state = pausing;
    return 1;
}
bool TRTask::UnpauseRecord() {
    assert(IsPausing()); ///should only be called from pause status
    recordingStartTime = time(NULL);
    
    state = recording;
    return 1;
}
void TRTask::Recover() {
    assert(backUpTask != NULL);
    taskName = backUpTask->taskName;
    lastDone = backUpTask->lastDone;
    timeDone = backUpTask->timeDone;
    timeElapsed = backUpTask->timeElapsed;
    recordingStartTime = backUpTask->recordingStartTime;

    TRTask *tmp = backUpTask;
    backUpTask = backUpTask->backUpTask;
    delete(tmp);
}
bool TRTask::IsRecording() {
    return state == recording;
}
bool TRTask::IsIdle() {
    return state == idle;
}
bool TRTask::IsPausing() {
    return state == pausing;
}
bool TRTask::StopRecord(bool isValid) { 
    ///isRecorded indicate whether the run is valid or not
    if (!IsActive()) return 0;
    PauseRecord();

    if (!isValid) {
        Recover();
    } else {
        AddTimeElapsed(recordingStoredTime);
        recordingStoredTime = 0;
        delete(backUpTask);
        backUpTask = NULL;
    }

    recordingStartTime = -1;
    state = idle;
    return 1;
}
void TRTask::SetDisplayTimeDone(bool display) {
    displayTimeDone = display;
}
void TRTask::SetDisplayLastDone(bool display) {
    displayLastDone = display;
}
void TRTask::SetDisplayTimeElapsed(bool display) {
    displayTimeElapsed = display;
}
bool TRTask::GetDisplayTimeDone() {
    return displayTimeDone;
}
bool TRTask::GetDisplayLastDone() {
    return displayLastDone;
}
bool TRTask::GetDisplayTimeElapsed() {
    return displayTimeElapsed;
}
std::string TRTask::ToString() {
    std::ostringstream result;
    result << GetName() << "\n";
    result << GetLastDone() << "\n";
    result << GetTimeDone() << "\n";
    result << GetTimeElapsed() << "\n";
    return result.str();
}
