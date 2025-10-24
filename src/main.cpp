#include <Arduino.h>
#include "time_slice.h"
#include "pid.h"
#include <Servo.h>
#include <NewPing.h>
#include "comm.h"

// put function declarations here:
//定义全局变量
Servo servo;
pid servo_pid;
float distance;

#define MAX_DISTANCE 25 // 最大距离（厘米）
const int trigPin = 7;
const int echoPin = 8;
NewPing sonar(trigPin, echoPin, MAX_DISTANCE);

String rx_buffer = "";


float readDistance() {
  // 使用ping_cm()方法，超时后会返回0
  unsigned int dist = sonar.ping_cm();
  
  if (dist == 0) {
    return 25.0f; // 超出范围
  }
  
  return (float)dist;
}



//定义回调函数
void pid_cb() {
    servo_pid.update(distance);
}

void servo_cb() {
    servo.write((int)(servo_pid.get_output()+0.5f));
}

void ultrasonic_cb() {
    distance = readDistance();
}

// 定义时间片
time_slice serial_task(100, serial_cb);
time_slice pid_task(100, pid_cb);
time_slice servo_task(250, servo_cb);
time_slice ultrasonic_task(50, ultrasonic_cb);
time_slice command_task(10, command_cb); 


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  servo.attach(9);
  servo.write(90);
  // 初始化超声波传感器引脚
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  //初始化PID参数
  servo_pid.kp = 0.0f;
  servo_pid.ki = 0.0f;
  servo_pid.kd = 0.0f;
  servo_pid.i_lm = 0.0f;
  servo_pid.output_lm = 0.0f;

  servo_pid.target = 10.0f;

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
