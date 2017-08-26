#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include "PQHeap.h"
#include "enemy.h"
#include "tower.h"
#include "main_functions.h"
#include "utility.h"

const int number_of_towers = 4;
int clock = -1;
vector<int> unpaved_distance(number_of_towers, 30); //30 is the initial unpaved distance

using namespace std;

int main()
{
	//Setting GUI (from base code)
	SetWindow();
	castle ct; // define castle 
	ct.Xstrt = CastleXStrt;
	ct.Ystrt = CastleYStrt;
	ct.W = CastleWidth;
	ct.L = CastleLength;


	float c1, c2, c3; //parameters
	vector<tower> towers; //initialize a vector of towers
	towers.reserve(number_of_towers);
	vector<PQHeap> priority_heaps; //initialize a vector of heaps, a heap for each tower
	priority_heaps.reserve(number_of_towers); 
	vector<enemy*> enemies; //initialize a vector of pointers to all enemies
	vector<enemy*> inactive_enemies; //initialize a vector of pointers to inactive enemies
	
	string line;
	ifstream infile("Input_Sample.txt");	
	int d = 1;
	if (infile.is_open()) {
		while (getline(infile,line)) {
			if (d == 1) { //get tower data
				float tower_health = stof(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ')+1);
				int tower_power, max_enemies;
				max_enemies = stoi(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ') + 1);
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
				line.erase(0, line.find(' ') + 1);
				c2 = stof(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ') + 1);
				c3 = stof(line);	
				d++;
			}
			else if (line.compare("-1") != 0) { //get enemies
				int seq = stoi(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ') + 1);
				int arrival_time = stoi(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ') + 1);
				float health = stof(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ') + 1);
				int power = stoi(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ') + 1);
				int delay_period = stoi(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ') + 1);
				int type = stoi(line.substr(0, line.find(' ')));
				line.erase(0, line.find(' ') + 1);
				char region = line[0];
				
				enemy* enem = new enemy(clock + 1, c1, c2, c3, seq, arrival_time, health, power, delay_period, type, region);
				enemies.push_back(enem);
				if (enem->wasInactive()) { //if was inactive and became active
					enem->calcPriority();
					priority_heaps[(enem->getRegion() - 'A')].insert_enemy(enem); //insert the active enemy in his heap depending on his region
				}
				else {
					inactive_enemies.push_back(enem);
				}
			}
		}
		infile.close();
	}

	//GUI
	DrawCastle(ct, 12, towers);
	DrawEnemies(enemies);

	//start main game loop
	int number_of_enemies = enemies.size();
	while (win_or_lose(towers, enemies, number_of_towers, number_of_enemies) == 0){
		clock++;
		
		//insert the newly active enemies in the heaps
		int num = inactive_enemies.size();
		for (int i = 0; i < num; i++){ 
			if (inactive_enemies[i]->wasInactive()) {
				inactive_enemies[i]->calcPriority();
				priority_heaps[(inactive_enemies[i]->getRegion() - 'A')].insert_enemy(inactive_enemies[i]);
			}
			inactive_enemies[i]->update_clock(clock);
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
			//update the towers health based on enemies attacking it, and update the enemies variables
			for (int j = 0; j < no_aggressive_enemies; j++) {
				auto &current_enemy = aggressive_enemies[j];
				current_enemy->updateDist(clock, &unpaved_distance[i]);
				float tower_damage = current_enemy->towerDamage();
				current_enemy->calcPriority();
				current_tower.setHealth(current_tower.getHealth() - tower_damage);
			}

			int no_defensive_enemies = current_tower.getMaxNumberEnemies();
			if (no_defensive_enemies > current_heap.heap_count()) no_defensive_enemies = current_heap.heap_count();
			auto defensive_enemies = current_heap.get_n_enems(no_defensive_enemies);
			//update the enemies health based on towers attacking it
			for (int j = 0; j < no_defensive_enemies; j++) {
				auto &current_enemy = defensive_enemies[j];
				float enem_damage = current_tower.enemy_damage(current_enemy->getDistance(), current_enemy->getType());
				//cout << current_enemy->getHealth() << '\n';
				current_enemy->setHealth(current_enemy->getHealth() - enem_damage);
				current_enemy->set_first_shot();
				if (current_enemy->isKilled()) {
					current_heap.delete_enem(current_enemy);
					current_enemy->set_fight_time();
				}
			}
			
			//re-sort the heap based on the newly calculated priorities
			current_heap.update_heap();
			DrawCastle(ct, 12, towers);
			DrawEnemies(enemies);
		}
	}

	ofstream Outfile("Output_Sample.txt");
	
	if (Outfile.is_open())
	{
		int num = enemies.size();
		for (int i = 0; i < num; i++) {
			auto enemy = enemies[i];
			Outfile << enemy->FT + enemy->getArrivalTime() << ' ' << enemy->getSequence() << ' ' << enemy->FD << ' ' << enemy->KD << ' ' << enemy->FT << '\n';
			cout << enemy->FT + enemy->getArrivalTime() << ' ' << enemy->getSequence() << ' ' << enemy->FD << ' ' << enemy->KD << ' ' << enemy->FT << '\n';
		}

		num = towers.size();
		for (int i = 0; i < num; i++) {
			cout << towers[i].getHealth() << ' ';
			Outfile << towers[i].getHealth() << ' ';
		}
		cout << endl;
		Outfile << endl;

		for (int i = 0; i < num; i++) {
			cout << unpaved_distance[i]  << ' ';
			Outfile << unpaved_distance[i] << ' ';
		}
		cout << endl;
		Outfile << endl;

		Outfile.close();
	}
	else cout << "Unable to open file";

	//delete the enemies objects which were created by new
	int num = enemies.size();
	for (int i = 0; i < num; i++)
		delete enemies[i];

	return 0;
}