#ifndef TRIPLE_H
#define TRIPLE_H
#include <string>
using  namespace std;
class Triple
{
    int PlayerId;
    double angle;
    double power;
public:
    Triple(int id_, double angle_, double power_);
    void set_player_id (int PlayerId_);
    void set_angle (double angle_);
    void set_power (double power_);
    string toString(void);
};

#endif // TRIPLE_H
