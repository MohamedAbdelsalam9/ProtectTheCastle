#ifndef MAIN_FUNCTIONS_H
#define MAIN_FUNCTIONS_H
#include <iostream>
#include <vector>
#include "PQHeap.h"
#include "enemy.h"
#include "tower.h"

int win_or_lose(vector<tower> &towers, vector<PQHeap> &priority_heaps, int number_of_towers); //if it is win return 1, if it is lose, return -1, else, return 0

//if a castle was destroyed
void update_enemies_region(PQHeap &priority_heap, int number_of_towers);
void merge_two_towers_heaps(PQHeap &old_heap, PQHeap &new_heap); 

#endif // MAIN_FUNCTIONS_H
