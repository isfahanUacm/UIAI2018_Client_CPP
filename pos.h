#ifndef POS_H
#define POS_H

class Pos
{
    double x;
    double y;

public:
    Pos();
    Pos(double x_ , double y_) : x(x_) , y(y_) {}

    double get_y();
    double get_x();

//private:
//    void set_x(double x_);
//    void set_y(double y_);
//    void set_x_and_y(double x_ , double y_);

};

#endif // POS_H
