#pragma once

// Holds value for a single elevator request.
class Job 
{
private:
    int people = 0;
    int floorDestination = 0;
    int currentFloor = 0;
    int direction = 0;
    bool bInside = false;

public:
    // Getters & Setters
    int GetPeople();

    int GetFloorDestination();

    int GetCurrentFloor();

    int GetDirection();

    int GetInside();
};
