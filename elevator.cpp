#include "elevator.h"

Elevator::Elevator(int param_capacity, int param_floorLimit, int param_currFloor)
    : capacity(param_capacity), floorLimit(param_capacity), currFloor(param_currFloor)
{   
}

// Takes in a elevator request.
void Elevator::AddRequest(Job& request)
{
    request.SetQueue(jobQueueTracker);

    // Reference the first queue we get.
    if (upJobLines.size() == 0 && downJobLines.size() == 0 && first == nullptr)
    {
        first = &request;   
        return;
    }

    if (request.GetDirection() == UP)
    {
        upJobLines.emplace(request);
    }
    else if (request.GetDirection() == DOWN)
    {
        downJobLines.emplace(request);
    }

    ++jobQueueTracker;
}

std::queue<Job> Elevator::GetElevatorQueue()
{
    if (first == nullptr)
    {
        std::cout << "No requests inserted. Please try again." << std::endl;
        return jobBank;
    }

    // Construct and insert our first job.
    int currDir = this->currFloor < first->GetFloorDestination() ? UP : DOWN;
    AddQueue(*first, currDir);

    while (upJobLines.size() != 0 || downJobLines.size() != 0)
    {
        bool continueUp = jobBank.back().GetCurrentFloor() <= upJobLines.front().GetCurrentFloor();
        bool continueDown = jobBank.back().GetCurrentFloor() >= downJobLines.front().GetCurrentFloor();

        /*
        If we are going up and find more queues that are on the way, add them into the main job queue.
        Vice versa for going down as well.
        */
        if ((currDir == UP && continueUp) || downJobLines.empty())
        {
            UpdateJobQueue(upJobLines, UP);
        }
        else if ((currDir == DOWN && continueDown) || upJobLines.empty())
        {
            UpdateJobQueue(downJobLines, DOWN);
        }
        else
        {
            if (!continueUp && !continueDown)
            {
                // Pick the one with the lowest queue number and process it into the main job queue.
                if (upJobLines.front().GetQueue() < downJobLines.front().GetQueue())
                {
                    UpdateJobQueue(upJobLines, UP);
                    currDir = UP;
                }
                else
                {
                    UpdateJobQueue(downJobLines, DOWN);
                    currDir = DOWN;
                }
            }
            else
            {
                currDir *= -1;
            }
        }
    }

    return jobBank;
}

void Elevator::UpdateJobQueue(std::queue<Job>& jobLine, int direction)
{
    AddQueue(jobLine.front(), direction);
    jobLine.pop();
}

void Elevator::AddQueue(Job& request, int direction)
{
    if (this->currFloor == request.GetCurrentFloor() || request.GetInside())
    {
        jobBank.push(request);
    }   
    else
    {
        // Current request is not on the same floor, we create a new request to get to desired request first.
        Job temp(0, request.GetCurrentFloor(), currFloor, direction, false);  
        jobBank.push(temp);
        jobBank.push(request);   
    }    
    currFloor = request.GetFloorDestination();
}

// Resets Elevator for later use.
void Elevator::ResetElevator()
{
    jobQueueTracker = 0;
    first = nullptr;   
    EmptyQueue(upJobLines);
    EmptyQueue(downJobLines);
    EmptyQueue(jobBank);
}

void Elevator::EmptyQueue(std::queue<Job>& queue)
{
    std::queue<Job> empty;
    std::swap(queue, empty);
}