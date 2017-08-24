#include <iostream>
#include <vector>
#include "PQHeap.h"
#include "enemy.h"
#include "tower.h"
#include "main_functions.h"

int win_or_lose(vector<tower> &towers, vector<PQHeap> &priority_heaps, int number_of_towers) {
	int towers_destroyed;
	int regions_without_enemies;
	for (int i = 1; i < number_of_towers; i++) {
		if (towers[i].is_destroyed())
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

void update_enemies_region(PQHeap &priority_heap, int number_of_towers) 
{
	auto enemies = priority_heap.get_n_enems(priority_heap.heap_count());
	int num = enemies.size();
	char old_region = enemies[0]->getRegion();
	char new_region;
	if ((old_region + 1 - 'A') > number_of_towers) new_region = 'A';
	else new_region = old_region + 1;
	for (int i = 0; i < num; i++) {
		enemies[i]->setRegion(new_region);
		enemies[i]->setDistance(30);
	}
}

void merge_two_towers_heaps(PQHeap &old_heap, PQHeap &new_heap)
{
	auto enemies = old_heap.get_n_enems(old_heap.heap_count());
	int num = enemies.size();
	for (int i = 0; i < num; i++) {
		new_heap.insert_enemy(enemies[i]);
	}
	old_heap.clear_heap();
}
