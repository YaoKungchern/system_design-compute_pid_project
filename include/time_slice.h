#ifndef TIME_SLICE_H
#define TIME_SLICE_H

#include<Arduino.h>

class time_slice {
public:
  time_slice(unsigned long interval, void (*task)(void));
  void update();
  bool isReady();
  void run();
  
private:
  unsigned long interval;
  unsigned long lastTime;
  void (*callback)(void);
};

#endif