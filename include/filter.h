#ifndef FILTER_H
#define FILTER_H

class kalman_filter
{
    public:
        kalman_filter(float q, float r);
        void update(float measured);
        float get_checked();
    private:
        float x;    //估计值
        float p;    //方差
        float q;    //过程噪声协方差
        float r;    //观测噪声协方差
        float k;    //卡尔曼增益
        float checked;
        
};

class mean_filter
{
    public:
        mean_filter(unsigned short queue_len);
        void update(float measured);
        float get_checked();
        ~mean_filter();  // 析构函数

    private:
        unsigned short queue_len;
        float* queue;
        unsigned short queue_ptr;
        float checked;
        float sum;
        
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