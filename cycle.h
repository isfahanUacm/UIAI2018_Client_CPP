#ifndef CYCLE_H
#define CYCLE_H


class Cycle
{
private:
    int cycleNum = 0;
    Team *MyTeam;
    Team *OppTeam;
    Ball *ball;

public:
    Cycle();
    ~Cycle();

};

#endif // CYCLE_H
