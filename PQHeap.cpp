#include "PQHeap.h"
#include <vector>
#include <iostream>
#include "enemy.h"
#include <math.h>
#include <iomanip>

using namespace std;

PQHeap::PQHeap(int initialCapacity)
{
    heapArray.reserve(++initialCapacity);
	heapArray.push_back(nullptr); //as the 0th element won't be used
}

PQHeap::~PQHeap(){}

void PQHeap::insert_enemy (enemy* enemyptr)
{
    if (empty_heap()){
        heapArray.push_back(enemyptr);
    }
    else {
        heapArray.push_back(enemyptr);
		for (int i = heap_count(); i > 1; i /= 2) {
			if (heapArray[i]->getPriority() > heapArray[i/2]->getPriority())
				swap_elements(i, i / 2);
			else
				return;
		}
    }
}

bool PQHeap::empty_heap()
{
    if (heap_count() <= 0) //as the 0th element is just a null pointer
        return true;
    else
        return false;
}

int PQHeap::heap_count()
{
    return heapArray.size()-1; //ignore the 0th element
}

void PQHeap::swap_elements(int ind1, int ind2) 
{
	enemy* temp = heapArray[ind1];
	heapArray[ind1] = heapArray[ind2];
	heapArray[ind2] = temp;
}

void PQHeap::print_heap()
{
	if (empty_heap()) return;

	int max = heap_count();
	int levels = (int)log2(max);
	for (int i = 0; i <= levels; i++) {
		for (int j = (int)pow(2, i); j < pow(2, i + 1) && j <= max; j++) {
			if (j == 1)
				cout << heapArray[j]->getPriority() << '\t';
			else
				cout << heapArray[j]->getPriority() << '(' << heapArray[j/2]->getPriority() << ')' << "     ";
		}
		cout << endl;
	}
	cout << endl;
}

enemy* PQHeap::get_max()
{
	return heapArray[1];
}

enemy* PQHeap::delete_max()
{
	enemy* temp = heapArray[1];
	heapArray[1] = heapArray[heap_count()];
	heapArray.pop_back();

	int i;
	for (i = 1; (i * 2) + 1 <= heap_count();) { //applies only if the node has two children
		if (heapArray[i]->getPriority() < heapArray[i * 2]->getPriority() || heapArray[i]->getPriority() < heapArray[(i * 2) + 1]->getPriority()) {
			if (heapArray[i * 2]->getPriority() > heapArray[(i * 2) + 1]->getPriority()) {
				swap_elements(i, i * 2);
				i = i * 2;
			}
			else {
				swap_elements(i, (i * 2) + 1);
				i = (i * 2) + 1;
			}
		}
		else
			return temp;
	}
	if ((i * 2) == heap_count()) { //corner case if the next to last node has one child and not two
		if (heapArray[i]->getPriority() < heapArray[i * 2]->getPriority())
			swap_elements(i, i * 2);
	}

	return temp;
}

enemy* PQHeap::delete_enem(enemy* enemyptr)
{
	int max = heap_count();
	int ind = 1;
	while (ind <= max && enemyptr != heapArray[ind])
		ind++;

	if (ind > max)
		return enemyptr; //enemyptr is not in the heap array
	else {
		heapArray[ind] = heapArray[max];
		heapArray.pop_back();
	}

	int i;
	for (i = ind; (i * 2) + 1 <= heap_count();) { //applies only if the node has two children
		if (heapArray[i]->getPriority() < heapArray[i * 2]->getPriority() || heapArray[i]->getPriority() < heapArray[(i * 2) + 1]->getPriority()) {
			if (heapArray[i * 2]->getPriority() > heapArray[(i * 2) + 1]->getPriority()) {
				swap_elements(i, i * 2);
				i = i * 2;
			}
			else {
				swap_elements(i, (i * 2) + 1);
				i = (i * 2) + 1;
			}
		}
		else
			return enemyptr;
	}
	if ((i * 2) == heap_count()) { //corner case if the next to last node has one child and not two
		if (heapArray[i]->getPriority() < heapArray[i * 2]->getPriority())
			swap_elements(i, i * 2);
	}
	return enemyptr;
}

void PQHeap::update_heap() //resort the heap
{
	vector<enemy*> tempHeapArray = heapArray;
	int count = heap_count();
	clear_heap(); //clears the heapArray
	for (int i = 1; i <= count; i++)
		insert_enemy(tempHeapArray[i]);
}

void PQHeap::clear_heap()
{
	heapArray.erase(heapArray.begin()+1, heapArray.end());
}