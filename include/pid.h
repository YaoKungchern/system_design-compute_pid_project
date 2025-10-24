#ifndef PID_H
#define PID_H

#include "time_slice.h"

class pid{
public:
    pid();

    float kp, ki, kd;
    float output_lm, i_lm;
    float target; 

    //void set_setpoint(float setpoint);
    void update(float input);
    float get_output();
    void reset();
private:
    float last_time;
    float last_error, error, error_sum, error_diff;
    float dt;
    float output;
};

#endif