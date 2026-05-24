#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <string>
#include <vector>

struct ScheduledTask {
    std::string name;
    int periodSeconds;
    int lastRunTime;
    int priority;
};

class Scheduler {
private:
    std::vector<ScheduledTask> tasks;

public:
    bool shouldRun(int currentTime, int period) const;

    void registerTask(const std::string& name, int periodSeconds, int priority);
    bool shouldRunTask(const std::string& name, int currentTime);
};

#endif
