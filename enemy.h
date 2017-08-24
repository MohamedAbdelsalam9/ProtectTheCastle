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

        // to update distance according to time steps, unpaved is the unpaved distance
        void updateDist(int new_clock, int* unpaved); 

        bool isActive();

		bool wasInactive(); //if was inactive and became active this timestep

        float towerDamage();

        bool isKilled();

		bool isPaver();

		void set_first_shot();

		void set_fight_time();
	
		int FD;
		int KD;
		int FT;

    private:
        float c1,c2,c3; // priority prarameters
        int s; // sequence
        int AT; // Arrival Time
        float h; //health
        int p; //power
        int pr; //hit period
        int ty; // type
        char R; //  region
		int D = 60; //distance
        float priority;
        int clock;
        int speed;
		int active;
		bool firstShot = false;
};
#endif // ENEMY_H