// time_slice.cpp
#include "time_slice.h"

time_slice::time_slice(unsigned long interval, void (*callback)(void)) {
  this->interval = interval;
  this->lastTime = millis();  // 初始化lastTime
  this->callback = callback;
}

void time_slice::update() {
  lastTime = millis();
}

bool time_slice::isReady() {
  return millis() - lastTime >= interval;
}

void time_slice::run() {
  if (isReady()) {
    callback();
    update();
  }
}

