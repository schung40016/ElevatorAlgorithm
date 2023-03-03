#include "job.h"

Job::Job(int param_people, int param_floorDestionation, int param_currentFloor, int param_direction, bool param_bInside)
    : people(param_people), floorDestination(param_floorDestionation), currentFloor(param_currentFloor), direction(param_direction), bInside(param_bInside)
{
}

// Getters & Setters
void Job::SetQueue(int param_queue)
{
    queue = param_queue;
}

int Job::GetPeople()
{
    return people;
}

int Job::GetFloorDestination()
{
    return floorDestination;
}

int Job::GetCurrentFloor()
{
    return currentFloor;
}

int Job::GetDirection()
{
    return direction;
}

int Job::GetInside()
{
    return bInside;
}

int Job::GetQueue()
{
    return queue;
}