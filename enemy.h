#ifndef ENEMY_H
#define ENEMY_H


class enemy
{
    public:
        enemy(int c);
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

        void updateVars();

        bool isActive(); // to update distance and priority according to time steps


    protected:

    private:
        float c1,c2,c3; // priority prarameters
        int s; // sequence
        int t; // time
        int h; //health
        int p; //power
        int pr; //hit period
        char ty,R; // type and region
        int D=60; //distance
        float priority;
        int clock;


};

#endif // ENEMY_H
