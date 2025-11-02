#include "pid.h"

/**
 * @brief PID控制器构造函数
 * @param kp 比例系数
 * @param ki 积分系数
 * @param kd 微分系数
 * @param output_lm 输出限幅值
 * @param i_lm 积分限幅值
 * @param target 目标值
 */
pid::pid(float kp, float ki, float kd, float output_lm, float i_lm, float target)
{ 
    this->last_time = micros();
    this->kp = kp; 
    this->ki = ki;
    this->kd = kd;
    this->output_lm = output_lm;
    this->i_lm = i_lm;
    this->target = target;
}

void pid::update(float input)
{ 
    last_error = error;
    float dt;
    dt = (micros() - last_time) / 1000000.0f;
    error = target - input;
    error_sum += error * dt;
    error_diff = (error - last_error) / dt;
    if(abs(error_sum * ki) > i_lm) error_sum = i_lm*error_sum/abs(error_sum)/ki;
    output = kp * error + ki * error_sum + kd * error_diff;
    if (abs(output) > output_lm) output = output_lm*output/abs(output);
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
}

/*__||_____||__
  __||_____||__
  ___\\___//___
  _===========_
  _____|||_____
  _____|||_____
  ______|______
  ___防伪专用___*/