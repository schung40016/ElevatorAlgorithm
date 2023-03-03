#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include "job.h"

/*
Elevator Behavior:
- As the elevator is going down, it will pick up any new requests that are also going down.
- As the elevator is going up, it will pick up any new requests that are also going up.
- Once the elevator is finished completed all requests that are going one direction (not all), then it will start 
  taking orders in the opposite direction. 
*/ 

constexpr int UP = 1;
constexpr int DOWN = -1;

class Elevator 
{
private:
    int capacity = 0;       // Number of people fit in the elevator.
    int floorLimit = 0;
    int currFloor = 0;
    int jobQueueTracker = 0;
    Job* first = nullptr;
    std::queue<Job> jobBank = {};
    std::queue<Job> upJobLines = {};
    std::queue<Job> downJobLines = {};

public:
    Elevator(int param_capacity, int param_floorLimit, int param_currFloor);

    void AddRequest(Job& request);

    std::queue<Job> GetElevatorQueue();

    void AddQueue(Job& request, int direction);
};