#ifndef PINHEAD_JOYSTICK_H
#define PINHEAD_JOYSTICK_H

#include <stdint.h>
#include <stdbool.h>

typedef struct {
    float x;
    float y;
    float range_x;
    float range_y;
    float deadzone;
} JoystickState;

void joystick_init(JoystickState *j);
void joystick_set_from_knobs(JoystickState *j, float raw_x, float raw_y);
float joystick_mod_x(const JoystickState *j);
float joystick_mod_y(const JoystickState *j);
void joystick_set_range_x(JoystickState *j, float r);
void joystick_set_range_y(JoystickState *j, float r);

#endif
