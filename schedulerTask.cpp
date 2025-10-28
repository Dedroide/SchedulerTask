#include "schedulerTask.h"

// Constructor initializes the SchedulerTask with no tasks
SchedulerTask::SchedulerTask() : numTasks(0) {}

/* Adds a task with the default interval and enabled by default
   unsigned char addTask(void (*function)()) returns the task ID or 255 if it fails
*/
unsigned char SchedulerTask::addTask(void (*f)()) {
    return addTask(f, DEFAULT_TASK_TIME, true);
}

/* Adds a task with a specified interval and enabled/disabled state
   unsigned char addTask(void (*function)(), unsigned long interval, bool enb)
   returns the task ID or 255 if it fails
*/
unsigned char SchedulerTask::addTask(void (*f)(), unsigned long interval, bool enb) {
    if (numTasks < MAX_TASKS) {
        tasks[numTasks].taskFunction = f;
        tasks[numTasks].lastRunTime = micros();
        tasks[numTasks].enabled = enb;
        tasks[numTasks].interval = interval;
        numTasks++;
        return numTasks - 1; // Return the task ID (index)
    }
    return 255; // Return an invalid value (255) to indicate failure
}

/* Enables or disables a task by its ID
   void enableTask(uint8_t taskId, bool enable)
*/
void SchedulerTask::enableTask(uint8_t taskId, bool enable) {
    if (taskId < numTasks) {
        if(tasks[taskId].enabled != enable){
        tasks[taskId].enabled = enable;
    // When enabling the task, update the last run time
    // to avoid it running immediately due to an
    // old lastRunTime value.
        if (enable) {
            tasks[taskId].lastRunTime = micros();
        }
    }
    }
}

/* Removes a task by its ID
   bool removeTask(uint8_t taskId)
   returns true on success, false on failure
*/
bool SchedulerTask::removeTask(uint8_t taskId) {
    if (taskId >= numTasks) {
        return false; // Invalid taskId
    }

    // Shift all subsequent tasks one position to the left
    for (uint8_t i = taskId; i < numTasks - 1; i++) {
        tasks[i] = tasks[i + 1];
    }

    numTasks--;
    tasks[numTasks].taskFunction = nullptr; // Clear the last element
    return true;
}

/* Changes the interval of a task by its ID
   bool changeInterval(uint8_t taskId, unsigned long newInterval)
   returns true on success, false on failure
*/
bool SchedulerTask::changeInterval(uint8_t taskId, unsigned long newInterval) {
    if (taskId < numTasks) {
        tasks[taskId].interval = newInterval;
        return true;
    }
    return false;
}

/* Runs all tasks that are enabled and ready to execute
   void runAll()
*/
void SchedulerTask::runAll() {
    unsigned long now = micros();
    for (uint8_t i = 0; i < numTasks; i++) {
        if (tasks[i].enabled && tasks[i].taskFunction != nullptr) {
            if ((now - tasks[i].lastRunTime) >= tasks[i].interval) {    
                tasks[i].lastRunTime = now;
                tasks[i].taskFunction();            }
        }
    }
}