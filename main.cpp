#include <iostream>
#include "PQHeap.h"
#include "enemy.h"
#include "tower.h"

const int number_of_towers = 4;
int clock = 0;
vector<int> unpaved_distance(number_of_towers, 30); //30 is the initial unpaved distance

using namespace std;

int win_or_lose(vector<tower> &towers ,vector<PQHeap> &priority_heaps); //if it is win return 1, if it is lose, return -1, else, return 0

int main()
{
	//Read tower values from file
	char Region = 'A';
	float tower_health; ////
	int tower_power, max_enemies; ////
	vector<tower> towers;
	towers.reserve(number_of_towers);
	vector<PQHeap> priority_heaps;
	priority_heaps.reserve(number_of_towers); //a heap for each tower
	for (int i = 0; i < number_of_towers; i++) {
		Region += i;
		towers.push_back(tower(Region, tower_health, tower_power, max_enemies));
		priority_heaps.push_back(PQHeap());
	}

	
	//Read tower values from file
	vector<enemy> enemies;
	int no_of_enemies;
	for (int i = 0; i < no_of_enemies; i++) {
		char region; ////
		float c_1, c_2, c_3, health; ////
		int seq, arrival_time, power, delay_period, type;
		enemies.push_back(enemy(clock, c_1, c_2, c_3, seq, arrival_time, health, power, delay_period, type, Region));
		if (enemies[i].wasInactive()) { //if was inactive and became active
			enemies[i].calcPriority();
			priority_heaps[(int)(enemies[i].getRegion()-'A')].insert_enemy(&enemies[i]); //insert the active enemy in his heap depending on his region
		}
	}

	

}


int win_or_lose(vector<tower> &towers, vector<PQHeap> &priority_heaps) {
	int towers_destroyed;
	int regions_without_enemies;
	for (int i = 1; i < number_of_towers; i++) {
		if (towers[i].getHealth() <= 0)
			towers_destroyed++;
		if (priority_heaps[i].heap_count <= 0)
			regions_without_enemies++;
	}
	if (towers_destroyed == number_of_towers)
		return -1; //lose
	else if (regions_without_enemies == number_of_towers)
		return 1; //win
	else
		return 0; //game still playing
}