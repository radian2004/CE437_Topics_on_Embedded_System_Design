
#include "SIGNAL.h"
// Define movement signals for different states
uint8_t LEFT[]          = { 1, 0, 0, 0, 0, 0, 0, 0 };          // Move left
uint8_t RIGHT[]         = { 2, 0, 0, 0, 0, 0, 0, 0 };          // Move right
uint8_t FORWARD[]       = { 3, 0, 0, 0, 0, 0, 0, 0 };          // Move forward
uint8_t BACKWARD_LEFT[] = { 4, 1, 0, 0, 0, 0, 0, 0 };          // Move backward left
uint8_t BACKWARD_RIGHT[]= { 4, 2, 0, 0, 0, 0, 0, 0 };          // Move backward right
uint8_t FORWARD_LEFT[]  = { 3, 1, 0, 0, 0, 0, 0, 0 };          // Move forward left
uint8_t FORWARD_RIGHT[] = { 3, 2, 0, 0, 0, 0, 0, 0 };          // Move forward right

uint8_t returnSignal = 0;	// Return signal from the actuator system

uint8_t Get_State(int distance1, int distance2, uint8_t *forceChange, uint8_t state)
{
	if (*forceChange == 0) {
		// No forced state change
		if (distance2 < distance1) {
			// Right side is closer
			if (distance2 <= 100)
				return BACKWARD_RIGHT_STATE;	// Object too close on the right
			else if (distance2 <= 900)
				return LEFT_STATE;				// Turn left to avoid
		}
		else if (distance1 < distance2) {
			// Left side is closer
			if (distance1 <= 100)
				return BACKWARD_LEFT_STATE;		// Object too close on the left
			else if (distance1 <= 900)
				return RIGHT_STATE;				// Turn right to avoid
		}

	}
	else if (*forceChange == 1) {
		// Enforce a counter-state transition
		*forceChange = 0;						// Reset force change flag
		return Get_CounterState(state);
	}
	return FORWARD_STATE;						// Default to forward movement
}

uint8_t Get_CounterState(uint8_t state)
{
	if (state == RIGHT_STATE) {
		return LEFT_STATE;						// Opposite of RIGHT is LEFT
	} else if (state == LEFT_STATE) {
		return RIGHT_STATE;						// Opposite of LEFT is RIGHT
	} else {
		return LEFT_STATE;						// Default counter-state is LEFT
	}
}

