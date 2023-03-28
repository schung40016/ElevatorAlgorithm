#include <iostream>

#include "elevator.h"

int main()
{
    // Create Elevator object.
    Elevator elevator;

    // Make 10 requests for now.
    elevator.MakeRequest(1, Elevator::Request::Up);
    elevator.MakeRequest(4, Elevator::Request::Up);
    elevator.MakeRequest(3, Elevator::Request::Up);
    elevator.MakeRequest(7, Elevator::Request::Down);
    elevator.MakeRequest(10, Elevator::Request::Down);

    // Use a while loop
    while (elevator.Tick())
    {
        elevator.Print();
    }

    return 0;
};