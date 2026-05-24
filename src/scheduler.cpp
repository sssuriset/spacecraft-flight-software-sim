#include "scheduler.h"

bool Scheduler::shouldRun(int currentTime, int period) const {
    if (period <= 0) {
        return false;
    }

    return currentTime % period == 0;
}

void Scheduler::registerTask(const std::string& name, int periodSeconds, int priority) {
    if (periodSeconds <= 0) {
        return;
    }

    ScheduledTask task;
    task.name = name;
    task.periodSeconds = periodSeconds;
    task.lastRunTime = -periodSeconds;
    task.priority = priority;

    tasks.push_back(task);
}

bool Scheduler::shouldRunTask(const std::string& name, int currentTime) {
    for (ScheduledTask& task : tasks) {
        if (task.name == name) {
            if (currentTime - task.lastRunTime >= task.periodSeconds) {
                task.lastRunTime = currentTime;
                return true;
            }

            return false;
        }
    }

    return false;
}
