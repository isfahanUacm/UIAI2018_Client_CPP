#ifndef CONSTS_H
#define CONSTS_H

class Size
{
    double height;
    double width;
public:
    Size();
    Size(double h , double w) : height(h) , width(w) {}

    double get_height(){return height;}
    double get_width(){return width;}
};

class Consts
{
public:

    static Size field_size(); // set default Field_size
    static Size goal_size();  // set default Goal_size
    static double ball_radius();
    static double player_radius();
    static double friction;

}


#endif // CONSTS_H
