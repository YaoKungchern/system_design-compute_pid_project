#ifndef TIME_SLICE_H
#define TIME_SLICE_H

#include<Arduino.h>

/**
 * @brief delay no more
 * 
 */
class time_slice {
public:
  time_slice(unsigned long interval, void (*callback)(void));
  void update();
  bool isReady();
  void run();
  
private:
  unsigned long interval;
  unsigned long lastTime;
  void (*callback)(void);
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