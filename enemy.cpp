#include "enemy.h"


enemy::enemy(int c)
{
    clock=c;
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
	priority = 0;
	active = 0;
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
	if (ty == 2) speed = 2; //fighter
	else if (ty == 3) speed = 1; //shielded fighter
	else if (ty == 1) speed = 2; //paver
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

// to update distance according to time steps, unpaved is the unpaved distance
void enemy::updateDist(int new_clock, int* unpaved)
{
	if (isPaver() && D <= *unpaved) {
		if ((new_clock - AT) % pr) { //if he is not in his delay time
			D = D - (new_clock - clock) * p; //the paver speed in unpaved area is his fire power
			if (D < *unpaved) *unpaved = D; //if the distance walked by the paver is less than the paved distance, make that distance paved
		}
	}
	else {
		D = D - (new_clock - clock) * speed;
		if (D < *unpaved) D = *unpaved;
		else if (D < 2) D = 2;
	}
	clock = new_clock;
}

bool enemy::isActive()
{
	if ((clock - AT) >= 0 && !isKilled()) return true;
    else return false;
}

float enemy:: towerDamage()
{   
	float dam;
	if (isActive() && !isPaver()) //if is paver, no damage is inflicted on the tower
		dam = (float)p / D;
	else dam = 0;
	return dam;
}

bool enemy:: isKilled()
{
	if (h <= 0) {
		active = 0;
		return true;
	}
    else return false;
}

bool enemy::isPaver()
{
	if (ty == 1) return true;
}

bool enemy::wasInactive()
{
	if (isActive() && active == 0) {
		active = 1;
		return true;
	}
	else return false;
}

void enemy::set_first_shot() {
	if (!firstShot) {
		firstShot = true;
		FD = clock - AT;
	}
}

void enemy::set_fight_time() {
	FT = clock - AT;
	KD = FT - FD;
}