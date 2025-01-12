

#include "SIGNAL.h"
/* Constants ----------------------------------------------------------------*/
uint8_t LEFT[] 		= { 1, 0, 0, 0, 0, 0, 0, 0 };
uint8_t RIGHT[] 	= { 2, 0, 0, 0, 0, 0, 0, 0 };
uint8_t FORWARD[] 	= { 3, 0, 0, 0, 0, 0, 0, 0 };
uint8_t BACKWARD[] 	= { 4, 0, 0, 0, 0, 0, 0, 0 };
/**
 * @brief Determine the robot's movement state based on sensor distances.
 * @param distance1 Distance from the first sensor.
 * @param distance2 Distance from the second sensor.
 * @return Movement state (BACKWARD_STATE, LEFT_STATE, RIGHT_STATE, or FORWARD_STATE).
 */
uint8_t Get_State(int distance1, int distance2)
{
	if (distance1 <= 600 && distance2 <= 600)
		return BACKWARD_STATE;

	if (distance2 < distance1) {
		if (distance2 <= 900)
			return LEFT_STATE;
	}
	else if (distance1 < distance2) {
		if (distance1 <= 900)
			return RIGHT_STATE;
	}
	return FORWARD_STATE;
}
/**
 * @brief Get the counter (opposite) state for the given movement state.
 * @param state Current state (e.g., LEFT_STATE, RIGHT_STATE).
 * @return Counter state (e.g., RIGHT_STATE for LEFT_STATE).
 */
uint8_t Get_CounterState(uint8_t state)
{
	if (state == RIGHT_STATE) {
		return LEFT_STATE;
	}
	else if (state == LEFT_STATE) {
		return RIGHT_STATE;
	}
	else {
		return LEFT_STATE;	// Default fallback for invalid state
	}
}

