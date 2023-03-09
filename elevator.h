#pragma once

#include <assert.h>
#include <iostream>

class Elevator {
public: 
    enum class ElevatorState : int {
        Idle,
        Up,
        Down
    };
	
    enum class ElevatorDirection : int {
        Up,
        Down,
    };

    enum class Request : int {
        Up,
        Down, 
        Stop
    };

    struct ElevatorRequest {
        bool m_upRequest = false;
        bool m_downRequest = false;
        bool m_stopRequest = false;
    };

    // Getters.
    ElevatorState GetElevatorState() const { return m_state; }
	const ElevatorRequest& GetRequest(int floor) const { assert(floor > 0 && floor < NUM_FLOORS - 1); return m_currentRequests[floor - 1]; }    // Assert can be used like if statements to stop the program from executing if it is given a wrong input.
	int GetCurrentFloor() const { return m_currentFloorIndex + 1; }
	
	// Check various request states
	bool HasRequest(const ElevatorRequest& request) const;          // Const ensures that method can't change member variables, only read.
	bool HasRequestAbove() const;                                 
	bool HasRequestBelow() const;
	bool HasRequestOnCurrent() const;
	int GetNumRequests() const;
	
	// Elevator State Setters
	void ClearRequestsOnCurrent();      
	void SetState(ElevatorState state);
	void MakeRequest(int floor, Request request);
	
	// Call to process the elevator.
	// Returns true if the elevator has finished processing requests.
    // Use switch statement here to determine elevator's state.
	bool Tick();

	// Print elevator status.
	void Print() const;

private:
	static constexpr int BASE_FLOOR_INDEX = 0;
	static constexpr int NUM_FLOORS = 10;
	static constexpr int NUM_IDLE_TICKS = 5; // How long elevator should stay idle.
	
	// Current Floor the elevator is stationed on.
	int m_currentFloorIndex = BASE_FLOOR_INDEX;

	// NOT A QUEUE/LIST OF REQUESTS. Checks whether each floor has a request like a hash. 
	ElevatorRequest m_currentRequests[NUM_FLOORS];

	// State of the elevator
	ElevatorState m_state = ElevatorState::Idle;
	ElevatorDirection m_direction = ElevatorDirection::Up;
	int m_idleTicks = 0;
};