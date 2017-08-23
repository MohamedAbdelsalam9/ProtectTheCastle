#ifndef ENEMY_H
#define ENEMY_H


class enemy
{
    public:
        enemy();
        virtual ~enemy();

        int getSequence();
        void setSequence(int s);

        int getTime();
        void setTime(int t);

        int getHealth();
        void setHealth(int h);

        int getPower();
        void setPower(int p);

        int getPeriod();
        void setPeriod(int pr);

        char getType();
        void setType(char ty);

        char getRegion();
        void setRegion(char R);

        int getDistance();
        void setDistance(int D);

        float getPriority();
        void calcPriority();

        void setPriorityParams(int c1,int c2,int c3);

        void updateVars(); // to update distance and priority according to time steps


    protected:

    private:
        int c1,c2,c3; // priority prarameters
        int s; // sequence
        int t; // time
        int h; //health
        int p; //power
        int pr; //hit period
        char ty,R; // type and region
        int D=60; //distance
        float priority;


};

#endif // ENEMY_H
