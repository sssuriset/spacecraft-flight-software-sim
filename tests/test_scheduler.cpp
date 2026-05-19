#include <cassert>
#include <iostream>
#include "scheduler.h"

int main() {
    Scheduler scheduler;

    assert(scheduler.shouldRun(0, 1) == true);
    assert(scheduler.shouldRun(5, 5) == true);
    assert(scheduler.shouldRun(6, 5) == false);
    assert(scheduler.shouldRun(10, 2) == true);
    assert(scheduler.shouldRun(10, 0) == false);
    assert(scheduler.shouldRun(10, -1) == false);

    std::cout << "Scheduler tests passed." << std::endl;

    return 0;
}