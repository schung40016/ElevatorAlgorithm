#include <iostream>

#include "elevator.h"

int main()
{
    Elevator elevator(10, 10, 0);

    std::cout << "Welcome to the Elevator Queue!" << std::endl;

    // Create ten elevator jobs and add them as requests.
    Job req1(0, 5, 3, UP, true);
    Job req2(0, 10, 5, DOWN, true);
    Job req3(0, 7, 1, UP, true);
    Job req4(0, 8, 4, UP, true);
    Job req5(0, 1, 3, DOWN, true);
    Job req6(0, 9, 4, UP, true);
    
    std::cout << "Processed requests!" << std::endl;

    elevator.AddRequest(req1);
    elevator.AddRequest(req2);
    elevator.AddRequest(req3);
    elevator.AddRequest(req4);
    elevator.AddRequest(req5);
    elevator.AddRequest(req6);

    std::cout << "Added requests!" << std::endl;

    std::queue<Job> ans = elevator.GetElevatorQueue(); 
    std::cout << "Created elevator queue!" << std::endl;


    std::cout << "Size:  " << ans.size() << std::endl;
    while (!ans.empty())
    {
        std::cout << "Elevator Job " << ans.front().GetCurrentFloor() << ", " << ans.front().GetFloorDestination() << std::endl;
        ans.pop(); 
    }

    return 0;
};