#pragma once

#include "job.h"
#include <vector>

constexpr int UP = 1;
constexpr int DOWN = -1;

// Elevator should return a queue that has ordered on how a elevator behaves.

/*
Elevator Behavior:
- As the elevator is going down, it will pick up any new requests that are also going down.
- As the elevator is going up, it will pick up any new requests that are also going up.
- Once the elevator is finished completed all requests that are going one direction (not all), then it will start 
  taking orders in the opposite direction. 
*/ 

class Elevator 
{
private:
    int capacity = 0;       // Number of people fit in the elevator.
    int floorLimit = 0;
    std::vector<Job> jobLines;

public:
    void AddRequest(const Job& request);

    void GetElevatorQueue();
};