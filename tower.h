#ifndef TOWER_H
#define TOWER_H

using namespace std;

class tower
{
public:
	tower(char region, float tower_health, float tower_power, int max_enemies) {
		TH = tower_health;
		NE = max_enemies;
		TP = tower_power;
		R = region;
	}
	virtual ~tower() {};

	int getHealth() { return TH; }
	void setHealth(float tower_health) { TH = health; }

	int getPower() { return TP; }
	void setPower(int tower_power) { TP = tower_power; }

	char getRegion() { return R; }
	void setRegion(char region) { R = region; }

	//maximum number of enemies the tower can shoot
	int getMaxNumberEnemies() { return NE; }
	void setMaxNumberEnemies(int max_enemies) { NE = max_enemies; }

	//return inflicted damage on the enemy, enem_type is 1 for paver, 2 for fighter, 3 for shielded fighter
	float shoot_enemy(int distance, int enem_type) {
		int k = 1;
		if (enem_type == 3) k = 2; //enemy is shielded
		return 1 / (float)distance * TP * 1 / (float)k;
	}

	//set the tower as destroyed
	void set_destroyed() { if (TH <= 0) destroyed = 1; }
	bool is_destroyed() { if (destroyed == 1) return true; }

private:
	float TH; //Tower Health
	int NE; //Number of enemies tower can shoot
	int TP; //Tower Power
	char R; //Region
	int destroyed = 0; //is the towe
};

#endif // TOWER_H