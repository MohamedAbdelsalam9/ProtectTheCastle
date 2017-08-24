#ifndef ENEMY_H
#define ENEMY_H


class enemy
{
    public:
        enemy(int c);
        enemy(int c,float c_1,float c_2,float c_3,int seq, int time,int health,int power, int period,int type,char Region);
        virtual ~enemy();

        int getSequence();
        void setSequence(int s);

        int getTime();
        void setTime(int t);

        float getHealth();
        void setHealth(float h);

        int getPower();
        void setPower(int p);

        int getPeriod();
        void setPeriod(int pr);

        int getType();
        void setType(int ty);

        char getRegion();
        void setRegion(char R);

        int getDistance();
        void setDistance(int D);

        float getPriority();
        void calcPriority();

        void setPriorityParams(float c1,float c2,float c3);

        // to update distance and priority according to time steps, c is the external clock
        void updateVars(int c);

        bool isActive();

        float shootTower();

        bool isKilled();
  

    private:
        float c1,c2,c3; // priority prarameters
        int s; // sequence
        int t; // time
        float h; //health
        int p; //power
        int pr; //hit period
        int ty; // type
        char R; //  region
        int D=60; //distance
        float priority;
        int clock;
        int speed;
};
#endif // ENEMY_H