#include "elevator.h"

void Elevator::Print() const
{
    std::cout << "Elevator currently sits at floor: " << m_currentFloorIndex << "." << std::endl;
    std::cout << "Elevator is currently " << m_state << "." << std::endl;
    std::cout << "Elevator is heading " << m_direction << "." << std::endl;
}

// Call to process the elevator.
// Returns true if the elevator has finished processing requests.
// Use switch statement here to determine elevator's state.
bool Elevator::Tick()
{

}

void Elevator::ClearRequestsOnCurrent()
{
    m_currentRequests[m_currentFloorIndex].m_downRequest = false;
    m_currentRequests[m_currentFloorIndex].m_stopRequest = false;
    m_currentRequests[m_currentFloorIndex].m_upRequest = false;
}