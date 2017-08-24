#include <iostream>
#include <vector>
#include <fstream>
#include <string>
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
	float c1 = 1, c2 = 1, c3 = 1; //parameters
	vector<tower> towers;
	towers.reserve(number_of_towers);
	vector<PQHeap> priority_heaps;
	priority_heaps.reserve(number_of_towers); //a heap for each tower
	vector<enemy> enemies;
	vector<enemy> inactive_enemies;
	
	string line;
	ifstream infile("Input_Sample.txt");	
	int d = 1;
	if (infile.is_open()) {
		while (getline(infile,line)) {
			if (d == 1) { //get tower data
				float tower_health = stof(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ')); line.erase(0, 1);
				int tower_power, max_enemies;
				max_enemies = stoi(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ')); line.erase(0, 1);
				tower_power = stoi(line);
				d++;
				char Region = 'A';

				//initialize towers and their heaps
				for (int i = 0; i < number_of_towers; i++) {
					Region += i;
					towers.push_back(tower(Region, tower_health, tower_power, max_enemies));
					priority_heaps.push_back(PQHeap());
				}
			}
			else if (d == 2) { //get parameters
				c1 = stof(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ')); line.erase(0, 1);
				c2 = stof(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ')); line.erase(0, 1);
				c3 = stof(line);	
				d++;
			}
			else if (line.compare("-1") != 0) { //get parameters
				int seq = stoi(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ')); line.erase(0, 1);
				int arrival_time = stoi(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ')); line.erase(0, 1);
				float health = stof(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ')); line.erase(0, 1);
				int power = stoi(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ')); line.erase(0, 1);
				int delay_period = stoi(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ')); line.erase(0, 1);
				int type = stoi(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ')); line.erase(0, 1);
				char region = line[0];

				enemies.push_back(enemy(clock + 1, c1, c2, c3, seq, arrival_time, health, power, delay_period, type, region));
				auto enem = *(enemies.end() - 1);
				if (enem.wasInactive()) { //if was inactive and became active
					enem.calcPriority();
					priority_heaps[(int)(enem.getRegion() - 'A')].insert_enemy(&enem); //insert the active enemy in his heap depending on his region
				}
				else {
					inactive_enemies.push_back(enem);
				}
			}
		}
		infile.close();
	}


	//start main game loop
	while (win_or_lose(towers, priority_heaps, number_of_towers) == 0) {

		clock++;

		//insert the newly active enemies in the heaps
		int num = inactive_enemies.size();
		for (int i = 0; i < num; i++){ 
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


		//update each tower with it's enemies
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
			for (int j = 0; j < no_defensive_enemies; j++) {
				auto &current_enemy = defensive_enemies[j];
				float enem_damage = current_tower.enemy_damage(current_enemy->getDistance(), current_enemy->getType());
				current_enemy->setHealth(current_enemy->getHealth() - enem_damage);
				current_enemy->set_first_shot();
				if (current_enemy->isKilled()) {
					current_heap.delete_enem(current_enemy);
					current_enemy->set_fight_time();
				}
			}
			
			current_heap.update_heap();
		}
	}

}