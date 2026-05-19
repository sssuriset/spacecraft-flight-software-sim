#include "scheduler.h"

bool Scheduler::shouldRun(int currentTime, int period) const {
    if (period <= 0) {
        return false;
    }

    return currentTime % period == 0;
}