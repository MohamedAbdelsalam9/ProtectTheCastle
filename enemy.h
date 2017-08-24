#ifndef ENEMY_H
#define ENEMY_H


class enemy
{
    public:
        enemy(int c = 0);
        enemy(int c,float c_1,float c_2,float c_3,int seq, int arrival_time,float health,int power, int period,int type,char Region);
        virtual ~enemy();

        int getSequence();
        void setSequence(int s);

        int getArrivalTime();
        void setArrivalTime(int t);

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

        // to update distance and priority according to time steps, unpaved is the unpaved distance
        void updateVars(int new_clock, int unpaved); 

        bool isActive();

        float shootTower();

        bool isKilled();
  

    private:
        float c1,c2,c3; // priority prarameters
        int s; // sequence
        int AT; // Arrival Time
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