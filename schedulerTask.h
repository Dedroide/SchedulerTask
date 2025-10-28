#ifndef SCHEDULERTASK_H
#define SCHEDULERTASK_H

#include <Arduino.h>

#define DEFAULT_TASK_TIME 1000000UL // Default time: 1000ms in microseconds (1 second)
#define MAX_TASKS 20 // Maximum number of tasks the scheduler can manage

class SchedulerTask {
private:
    struct TaskEntry {
        unsigned long lastRunTime;  // Stores the last execution time in microseconds
        void (*taskFunction)();     // Pointer to the task function
        bool enabled;               // Indicates if the task execution is enabled        
        unsigned long interval;     // Time interval for this task
    };

    TaskEntry tasks[MAX_TASKS];
    uint8_t numTasks;

public:
    SchedulerTask();

    unsigned char addTask(void (*f)());
    unsigned char addTask(void (*f)(), unsigned long interval, bool enb = true);
    void enableTask(uint8_t taskId, bool enable);
    bool removeTask(uint8_t taskId);
    bool changeInterval(uint8_t taskId, unsigned long newInterval);
    void runAll();
};

#endif // SCHEDULERTASK_H