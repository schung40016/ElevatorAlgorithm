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

    // Main meat of the code is here.
    while (upJobLines.size() != 0 || downJobLines.size() != 0)
    {
        bool continueUp = jobBank.back().GetCurrentFloor() <= upJobLines.front().GetCurrentFloor();
        bool continueDown = jobBank.back().GetCurrentFloor() >= downJobLines.front().GetCurrentFloor();

        if ((currDir == UP && continueUp) || downJobLines.empty())
        {
            AddQueue(upJobLines.front(), UP);
            upJobLines.pop();
        }
        else if ((currDir == DOWN && continueDown) || upJobLines.empty())
        {
            AddQueue(downJobLines.front(), DOWN);
            downJobLines.pop();
        }
        else
        {
            if (!continueUp && !continueDown)
            {
                // Pick the one with the lowest queue number and add that to the 
                if (upJobLines.front().GetQueue() < downJobLines.front().GetQueue())
                {
                    AddQueue(upJobLines.front(), UP);
                    upJobLines.pop();
                    currDir = UP;
                }
                else
                {
                    AddQueue(downJobLines.front(), DOWN);
                    downJobLines.pop();
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

void Elevator::AddQueue(Job& request, int direction)
{
    std::cout << "Processing: " << request.GetCurrentFloor() << " == " << request.GetFloorDestination() << std::endl;
    if (this->currFloor == request.GetCurrentFloor())
    {
        jobBank.push(request);
    }   
    else
    {
        Job temp(0, request.GetCurrentFloor(), currFloor, direction, false);  
        jobBank.push(temp);
        jobBank.push(request);   
    }    
    currFloor = request.GetFloorDestination();
}