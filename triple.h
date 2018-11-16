#ifndef TRIPLE_H
#define TRIPLE_H
#include <string>
using  namespace std;
class Triple
{
private:
	friend class Game;
    int PlayerId;
    double angle;
    double power;
	string toString(void);
public:
    Triple();
    Triple(int id_, double angle_, double power_);
    void setPlayerID (int PlayerId_);
    void setAngle (double angle_);
    void setPower (double power_);

};

#endif // TRIPLE_H
