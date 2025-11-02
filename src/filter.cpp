#include "filter.h"

kalman_filter::kalman_filter(float q, float r)
{
    this->q = q;
    this->r = r;
    this->x = 0.0f;
    this->p = 1.0f;
    this->k = 0.0f;
    this->checked = 0.0f;
}

void kalman_filter::update(float measured)
{ 
    //预测
    float x_pred = x;
    float p_pred = p + q;
    //更新
    k = p_pred / (p_pred + r);
    x = x_pred + k * (measured - x_pred);
    p = (1 - k) * p_pred;

    checked = x_pred;
}

float kalman_filter::get_checked()
{
    return checked;
}

mean_filter::mean_filter(unsigned short queue_len)
{
    queue = new float[queue_len];  // 动态分配内存
    for (unsigned short i = 0; i < queue_len; i++) {
        queue[i] = 0.0f;
    }
    this->queue_len = queue_len;
    this->queue_ptr = 0;
    this->sum = 0.0f;
    this->checked = 0.0f;
}

void mean_filter::update(float measured)
{
    sum -= queue[queue_ptr];
    queue[queue_ptr] = measured;
    sum += measured;
    queue_ptr = (queue_ptr + 1) % queue_len;
    checked = sum / queue_len;
}

float mean_filter::get_checked()
{
    return checked;
}

mean_filter::~mean_filter()
{
    delete[] queue;  // 释放内存
}

/*__||_____||__
  __||_____||__
  ___\\___//___
  _===========_
  _____|||_____
  _____|||_____
  ______|______
  ___防伪专用___*/