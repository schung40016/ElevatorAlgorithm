#pragma once

// Holds value for a single elevator request.
class Job 
{   
private:
    int people = 0;
    int queue = 0;
    int floorDestination = 0;
    int currentFloor = 0;
    int direction = 0;
    bool bInside = false;

public:

    Job(int param_people, int param_floorDestionation, int param_currentFloor, int param_direction, bool param_bInside);

    // Getters & Setters
    void SetQueue(int param_queue);

    int GetPeople();

    int GetFloorDestination();

    int GetCurrentFloor();

    int GetDirection();

    int GetInside();

    int GetQueue();
};
