#ifndef COMM_H
#define COMM_H

#include <Arduino.h>
#include "pid.h"

extern String rx_buffer;
extern pid servo_pid;
extern float distance;

void command_cb();
void processCommand(String cmd);
void serial_cb();

#endif