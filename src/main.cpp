#include <Arduino.h>
#include "time_slice.h"
#include "pid.h"
#include <Servo.h>
#include <NewPing.h>
#include "comm.h"
#include "filter.h"

// put function declarations here:
//定义全局变量
Servo servo;
//初始化PID参数
pid servo_pid(0.2f, 0.001f, 400.0f, 15.0f, 12.0f, 7.0f);
//kp, ki, kd, lm,i_lm, t, target
float distance;

const int trig_pin = 7;
const int echo_pin = 8;
const int servo_pin = 9;
NewPing sonar(trig_pin, echo_pin, 20);

//初始化滤波器
mean_filter distance_mean_ft(5);
kalman_filter distance_kalman_ft(0.1f,0.4f);

String rx_buffer = "";


float readDistance() {
  // 使用ping_cm()方法，超时后会返回0
  unsigned int dist = sonar.ping_cm();
  if (dist == 0) {
    return 0.0f; // 超出范围
  }
  return (float)dist;
}



//定义回调函数
void pid_cb() {
    servo_pid.update(distance);
}

void servo_cb() {
    servo.write((int)(servo_pid.get_output()+90.5f));
}

void ultrasonic_cb() {
    distance_mean_ft.update(readDistance());
    distance_kalman_ft.update(distance_mean_ft.get_checked());
    distance = distance_kalman_ft.get_checked();
}

// 定义时间片
time_slice serial_task(100, serial_cb);
time_slice pid_task(25, pid_cb);
time_slice servo_task(50, servo_cb);
time_slice ultrasonic_task(25, ultrasonic_cb);
time_slice command_task(10, command_cb); 


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(servo_pin);
  servo.write(90);
  // 初始化超声波传感器引脚
  pinMode(trig_pin, OUTPUT);
  pinMode(echo_pin, INPUT);
  //初始化滤波器
  for(u8 i=0; i<5; i++)
  {
    ultrasonic_cb();
    delay(100);
  }

}

void loop() {
  // put your main code here, to run repeatedly:
  serial_task.run();
  pid_task.run();
  servo_task.run();
  ultrasonic_task.run();
  command_task.run();
}

// put function definitions here:
/*__||_____||__
  __||_____||__
  ___\\___//___
  _===========_
  _____|||_____
  _____|||_____
  ______|______
  ___防伪专用___*/
