#include "elevator.h"

void Elevator::Print() const
{
    std::cout << "Elevator currently sits at floor: " << m_currentFloorIndex << "." << std::endl;
    std::cout << "Elevator is currently " << static_cast<std::underlying_type<ElevatorState>::type>(m_state) << "." << std::endl;
    std::cout << "Elevator is heading " << static_cast<std::underlying_type<ElevatorDirection>::type>(m_direction) << "." << std::endl;
}

// Call to process the elevator.
// Returns true if the elevator has finished processing requests.
// Use switch statement here to determine elevator's state.
bool Elevator::Tick()
{
    return true;
}

// Checks for requests.
bool Elevator::HasRequest(const ElevatorRequest& request) const
{
    return request.m_downRequest || request.m_stopRequest || request.m_upRequest;
}

bool Elevator::HasRequestAbove() const 
{
    for (int i = m_currentFloorIndex + 1; i < NUM_FLOORS; ++i)
    {
        if (HasRequest(m_currentRequests[i]))
        {
            return true;
        }
    }
    return false;
}

bool Elevator::HasRequestBelow() const
{
    for (int i = m_currentFloorIndex - 1; i >= BASE_FLOOR_INDEX; --i)
    {
        if (HasRequest(m_currentRequests[i]))
        {
            return true;
        }
    }
    return false;
}

bool Elevator::HasRequestOnCurrent() const
{
    return HasRequest(m_currentRequests[m_currentFloorIndex]);
}

int Elevator::GetNumRequests() const
{
    int totalRequests = 0;

    for (int i = 0; i < NUM_FLOORS; ++i)
    {
        if (HasRequest(m_currentRequests[i]))
        {
            totalRequests++;
        }
    }

    return totalRequests;
}

// Reset current floor's requests default.
void Elevator::ClearRequestsOnCurrent()
{
    m_currentRequests[m_currentFloorIndex].m_downRequest = false;
    m_currentRequests[m_currentFloorIndex].m_stopRequest = false;
    m_currentRequests[m_currentFloorIndex].m_upRequest = false;
}

void Elevator::SetState(ElevatorState state)
{
    m_state = state;
}

void Elevator::MakeRequest(int floor, Request request)
{
    floor -= 1;
    if (floor > NUM_FLOORS || floor < BASE_FLOOR_INDEX)
    {
        std::cout << "Error processing floor input: " << floor << std::endl;
        return;
    }

    // Each floor is treated like a state machine
    switch(request)
    {
        case Request::Up: m_currentRequests[floor].m_upRequest = true;
                        break;
        case Request::Stop: m_currentRequests[floor].m_stopRequest = true;
                        break;
        case Request::Down: m_currentRequests[floor].m_downRequest = true;
                        break;
    }
}