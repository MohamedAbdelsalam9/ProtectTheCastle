#ifndef PQHEAP_H
#define PQHEAP_H
#include <vector>
#include "enemy.h"

using namespace std;

class PQHeap
{
    public:
        PQHeap(int initialCapacity = 10); //if no initial Capacity is specified, initialize by 10 elements
        //PQHeap(const vector<float>& init_vector); //if the user specified the array beforehand, use it. the alias to save memory instead of copying and the const so as to access the data read only
        virtual ~PQHeap();
        void insert_enemy (enemy* enemyptr); //const so as to not be able to change tha data inside the enemy //return true if successful
        int heap_count(); //number of nodes in the heap
		void print_heap();
		enemy* get_max();
		enemy* delete_max(); //returns the enemy pointer with max priority after removing it from the heap array (it doesn't delete the enemy from memory)
		enemy* delete_enem(enemy* enemyptr); //returns the specified enemy pointer after removing it from the heap array (it doesn't delete the enemy from memory)
		void update_heap(); //re-sort the heap if the node priorities changed
		void clear_heap(); //erase all the elements from the heap

    private:		
        vector<enemy*> heapArray; //store in the heap array the pointers to enemies
		bool empty_heap();
		void swap_elements(int ind1, int ind2); //swap elements in the heapArray by index
};

#endif // PQHEAP_H