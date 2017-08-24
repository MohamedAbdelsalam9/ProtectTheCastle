#include "enemy.h"


enemy::enemy(int c)
{
    clock=c;
    //ctor
}

enemy::enemy(int c,float c_1,float c_2,float c_3,int seq, int arrival_time,float health,int power, int period,int type,char Region)
{
	clock = c;
	c1 = c_1;
	c2 = c_2;
	c3 = c_3;
	s = seq;
	AT = arrival_time;
	h = health;
	p = power;
	pr = period;
	setType(type);
	R = Region;
}

enemy::~enemy() {}

int enemy::getSequence()
{
    return s;
}

void enemy::setSequence(int sequence)
{
    s= sequence;
}

int enemy::getArrivalTime()
{
    return AT;
}

void enemy::setArrivalTime(int time)
{
	AT = time;
}

float enemy::getHealth()
{
    return h;
}

void enemy::setHealth(float health)
{
	h = health;
}

int enemy::getPower()
{
    return p;
}

void enemy::setPower(int power)
{
	p = power;
}

int enemy::getPeriod()
{
    return pr;
}

void enemy::setPeriod(int period)
{
	pr = period;
}

int enemy::getType()
{
    return ty;
}
void enemy::setType(int type)
{
	ty = type;
	if (ty == 1) speed = 1;
	else if (ty == 2) speed = 2;
	else speed = 1;
}

char enemy::getRegion()
{
    return R;
}

void enemy::setRegion(char region)
{
	R = region;
}

int enemy::getDistance()
{
    return D;
}

void enemy::setDistance(int distance)
{
	D = distance;
}

float enemy::getPriority()
{
    return priority;
}

void enemy::calcPriority()
{
	priority = (p*c1 / (D*((pr - (clock - AT) % pr) + 1))) + h*c2 + c3*ty;
}

void enemy::setPriorityParams(float c_1,float c_2,float c_3)
{
	c1 = c_1;
	c2 = c_2;
	c3 = c_3;
}

// to update distance and priority according to time steps, unpaved is the unpaved distance
void enemy::updateVars(int new_clock, int unpaved)
{
	clock = c;

	D = D - speed;
	if (D < unpaved) D = unpaved;
	else if (D < 2) D = 2;

	calcPriority();
}

bool enemy::isActive()
{
	if ((t - clock) >= 0 && !isKilled()) return true;
    else return false;
}

float enemy:: shootTower()
{   
	float dam;
	if (isActive())
		dam = p / D;
	else dam = 0;
	return dam;
}

bool enemy:: isKilled()
{
	if (h <= 0) return true;
    else return false;
}