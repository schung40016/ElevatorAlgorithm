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
    // Treat each case like a state of our elevator machine.
    switch(GetElevatorState())
    {
        case ElevatorState::Idle: {
            if (m_idleTicks <= 0 )
            {
                // Finished waiting. 
                if (HasRequestOnCurrent())
                {
                    ClearRequestsOnCurrent();
                }
                
                switch(m_direction)
                {
                    case ElevatorDirection::Up: {
                        HasRequestAbove() ? SetState(ElevatorState::Up) : SetState(ElevatorState::Down);
                    }
                    case ElevatorDirection::Down: {
                        HasRequestBelow() ? SetState(ElevatorState::Down) : SetState(ElevatorState::Up);
                    }
                }
            }
            m_idleTicks--;
        }
        case ElevatorState::Up: {
            ElevatorRequest& temp = GetRequest(m_currentFloorIndex);

            // Only process requests that are doing in the same direction.
            if (HasRequestOnCurrent() && temp.m_upRequest)
            {
                SetState(ElevatorState::Idle);  // To process a request, the elevator must go idle.
                m_idleTicks = NUM_IDLE_TICKS;
            }
            else if (HasRequestAbove())
            {
                m_currentFloorIndex++;          // No requests on current, continue going up.
            } 
            else // We can go down from here.
            {
                SetState(ElevatorState::Down);
                m_direction = ElevatorDirection::Down;
            }
        }
        case ElevatorState::Down: {
            ElevatorRequest& temp = GetRequest(m_currentFloorIndex);

            // Only process requests that are doing in the same direction.
            if (HasRequestOnCurrent() && temp.m_downRequest)
            {
                SetState(ElevatorState::Idle);  // To process a request, the elevator must go idle.
                m_idleTicks = NUM_IDLE_TICKS;
            }
            else if (HasRequestBelow())
            {
                m_currentFloorIndex--;          // No requests on current, continue going up.
            } 
            else // No requests below, let's start heading up again.
            {
                SetState(ElevatorState::Up);
                m_direction = ElevatorDirection::Up;
            }
        }
    }

    return GetNumRequests == 0 ? true : false;
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