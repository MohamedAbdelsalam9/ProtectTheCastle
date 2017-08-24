#include "enemy.h"


enemy::enemy(int c)
{
    clock=c;
    //ctor
}

enemy::(int c,float c_1,float c_2,float c_3,int seq, int time,int health,int power, int period,int type,char Region)
{
    clock=c;
    c1=c_1;
    c2=c_2;
    c3=c_3;
    s=seq;
    t=time;
    h=health;
    p=power;
    pr=period;
    setType(type);
    R=Region;
}

enemy::~enemy()
{
    //dtor
}
int enemy::getSequence()
{
    return s;
}

void enemy::setSequence(int s)
{
    this.s=s;
}

int enemy::getTime()
{
    return t;
}
void enemy::setTime(int t)
{
    this.t=t;
}

int enemy::getHealth()
{
    return h;
}
void enemy::setHealth(int h)
{
    this.h=h;
}

int enemy::getPower()
{
    return p;
}
void enemy::setPower(int p)
{
    this.p=p;
}

int enemy::getPeriod()
{
    return pr;
}
void enemy::setPeriod(int pr)
{
    this.pr=pr;
}

int enemy::getType()
{
    return ty;
}
void enemy::setType(int ty)
{
    this.ty=ty;
    if(ty==1) speed=1;
    else if(ty==2) speed=2;
    else speed =1;
}

char enemy::getRegion()
{
    return R;
}
void enemy::setRegion(char R)
{
    this.R=R;
}

int enemy::getDistance()
{
    return D;
}
void enemy::setDistance(int D)
{
    this.D=D;
}

float enemy::getPriority()
{
    return priority;
}
void enemy::calcPriority()
{
    priority= (p*c1/(D*((pr-(clock-t)%pr)+1)))+h*c2+c3*ty;
}

void enemy::setPriorityParams(float c1,float c2,float c3)
{
    this.c1=c1;
    this.c2=c2;
    this.c3=c3;
}

void enemy::updateVars(int c)
{
    clock=c;
    D=D-(clock-t)*speed;
    if(D<2) D=2;
    calcPriority();

}

bool enemy::isActive()
{
    if((t-clock)>=0) return true;
    else return false;
}

float enemy:: shootTower()
{   float dam;
    if (isActive)
    {
        dam= p/D;
    } else dam=0;
    return dam
}

bool enemy:: isKilled()
{
    if(h=<0) return true;
    else return false;
}

 // to update distance and priority according to time steps

