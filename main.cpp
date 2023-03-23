#include <iostream>

#include "elevator.h"

int main()
{
    // Create Elevator object.
    Elevator elevator;

    // Make 10 requests for now.
    elevator.MakeRequest(1, Elevator::Request::Up);
    elevator.MakeRequest(4, Elevator::Request::Up);
    elevator.MakeRequest(7, Elevator::Request::Up);

    // Use a while loop
    int i = 5;

    while (elevator.Tick())
    {
        elevator.Print();
        //i--;

        if (i == 0)
        {
            break;
        }
    }

    return 0;
};