#ifndef PID_H
#define PID_H

#include <Arduino.h>

class pid{
public:
    pid(float kp, float ki, float kd, float output_lm, float i_lm, float target);

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
    float output;
};

#endif

/*__||_____||__
  __||_____||__
  ___\\___//___
  _===========_
  _____|||_____
  _____|||_____
  ______|______
  ___防伪专用___*/