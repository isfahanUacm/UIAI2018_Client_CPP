#ifndef POS_H
#define POS_H

class Pos
{
private:
    double x;
    double y;

public:
    Pos();
    Pos(double x_ , double y_) : x(x_) , y(y_) {}

    double get_y();
    double get_x();
};

#endif // POS_H
