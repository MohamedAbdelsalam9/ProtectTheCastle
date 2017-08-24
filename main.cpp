#include <iostream>
#include <vector>
#include "PQHeap.h"
#include "enemy.h"
#include "tower.h"
#include "main_functions.h"

const int number_of_towers = 4;
int clock = -1;
vector<int> unpaved_distance(number_of_towers, 30); //30 is the initial unpaved distance

using namespace std;

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
	vector<enemy> inactive_enemies;
	int no_of_enemies;
	for (int i = 0; i < no_of_enemies; i++) {
		char region; ////
		float c_1, c_2, c_3, health; ////
		int seq, arrival_time, power, delay_period, type;
		enemies.push_back(enemy(clock+1, c_1, c_2, c_3, seq, arrival_time, health, power, delay_period, type, Region));
		if (enemies[i].wasInactive()) { //if was inactive and became active
			enemies[i].calcPriority();
			priority_heaps[(int)(enemies[i].getRegion()-'A')].insert_enemy(&enemies[i]); //insert the active enemy in his heap depending on his region
		}
		else {
			inactive_enemies.push_back(enemies[i]);
		}
	}

	while (win_or_lose(towers, priority_heaps, number_of_towers) == 0) {
		clock++;
		for (int i = 0; i < inactive_enemies.size(); i++){ //insert the newly active enemies in the heaps
			if (inactive_enemies[i].wasInactive()) {
				inactive_enemies[i].calcPriority();
				priority_heaps[(int)(inactive_enemies[i].getRegion() - 'A')].insert_enemy(&inactive_enemies[i]);
			}
		}

		//check destroyed towers, if so, change tower and update distances
		for (int i = 0; i < number_of_towers; i++) {
			if (towers[i].is_destroyed()) {
				update_enemies_region(priority_heaps[i], number_of_towers);
				if (i+1 >= number_of_towers)
					merge_two_towers_heaps(priority_heaps[i], priority_heaps[0]);
				else
					merge_two_towers_heaps(priority_heaps[i], priority_heaps[i+1]);
			}
		}

		for (int i = 0; i < number_of_towers; i++) {
			auto &current_heap = priority_heaps[i];
			auto &current_tower = towers[i];
			int no_aggressive_enemies = current_heap.heap_count();
			auto aggressive_enemies = current_heap.get_n_enems(no_aggressive_enemies);
			for (int j = 0; j < no_aggressive_enemies; j++) {
				auto &current_enemy = aggressive_enemies[j];
				current_enemy->updateDist(clock, &unpaved_distance[i]);
				float tower_damage = current_enemy->towerDamage();
				current_enemy->calcPriority();
				current_tower.setHealth(current_tower.getHealth() - tower_damage);
			}

			int no_defensive_enemies = current_tower.getMaxNumberEnemies();
			auto defensive_enemies = current_heap.get_n_enems(no_defensive_enemies);
			
			
			current_heap.update_heap();
		}
	}

}