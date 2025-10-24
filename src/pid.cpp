#include "pid.h"

pid::pid()
{ 
    this->last_time = micros();
    this->dt = 0.0f;
}

void pid::update(float input)
{ 
    last_error = error;
    dt = (micros() - last_time) / 1000000.0f;
    error = target - input;
    error_sum += error * dt;
    error_diff = (error - last_error) / dt;
    if(ki * error_sum >= i_lm) error_sum = i_lm / ki;
    output = kp * error + ki * error_sum + kd * error_diff;
    if (output > output_lm) output = output_lm;
}

float pid::get_output()
{ 
    return output;
}

void pid::reset()
{ 
    error = 0.0f;
    error_sum = 0.0f;
    error_diff = 0.0f;
    last_error = 0.0f;
    last_time = micros();
    dt = 0.0f;
}