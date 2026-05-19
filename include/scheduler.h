#ifndef SCHEDULER_H
#define SCHEDULER_H

class Scheduler {
public:
    bool shouldRun(int currentTime, int period) const;
};

#endif