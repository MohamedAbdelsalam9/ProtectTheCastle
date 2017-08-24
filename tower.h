#ifndef TOWER_H
#define TOWER_H

using namespace std;

class tower
{
public:
	tower() {};
	tower(char region, float tower_health, int tower_power, int max_enemies) {
		TH = tower_health;
		NE = max_enemies;
		TP = tower_power;
		R = region;
	}
	virtual ~tower() {};

	float getHealth() { return TH; }
	void setHealth(float tower_health) { TH = tower_health; }

	int getPower() { return TP; }
	void setPower(int tower_power) { TP = tower_power; }

	char getRegion() { return R; }
	void setRegion(char region) { R = region; }

	//maximum number of enemies the tower can shoot
	int getMaxNumberEnemies() { return NE; }
	void setMaxNumberEnemies(int max_enemies) { NE = max_enemies; }

	//return inflicted damage on the enemy, enem_type is 1 for paver, 2 for fighter, 3 for shielded fighter
	float enemy_damage(int distance, int enem_type) {
		int k = 1;
		if (enem_type == 3) k = 2; //enemy is shielded
		return 1 / (float)distance * TP * 1 / (float)k;
	}

	//set the tower as destroyed
	bool is_destroyed() { 
		if (TH <= 0) return true;
		else return false;
	}

private:
	float TH; //Tower Health
	int NE; //Number of enemies tower can shoot
	int TP; //Tower Power
	char R; //Region
};

#endif // TOWER_H