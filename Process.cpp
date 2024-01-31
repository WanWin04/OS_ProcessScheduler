#include "Process.hpp"

Process::Process() : ID(0), arrivalTime(0), turnAroundTime(0), waitingTime(0), isWaiting(false), startReadyQueue(0), isPriority(true) {}

Process::~Process() {
    CPUBurst.clear();
    resourceBurst.clear();
}