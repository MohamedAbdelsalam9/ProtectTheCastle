#include <iostream>
#include "PQHeap.h"
#include "enemy.h"

using namespace std;

int main()
{
    PQHeap x(10);

	vector<enemy> enem(25);
	for (int i = 1; i <= 22; i++) {
		enem[i].calcPriority((float)i);
		x.insert_enemy(&enem[i]);
	}
	enem[23].calcPriority(0);
	x.insert_enemy(&enem[23]);

	x.print_heap();

	cout << x.delete_max()->getPriority()<<endl<<endl;
	cout << x.delete_enem(&enem[22])->getPriority() << endl << endl;
	cout << x.delete_enem(x.get_max())->getPriority() << endl << endl;

	x.print_heap();
	
	enem[20].calcPriority(enem[20].getPriority() - 2);
	enem[23].calcPriority(enem[23].getPriority() + 10);
	x.print_heap();
	x.update_heap();

	x.print_heap();

	vector<enemy*> new_enems = x.get_n_enems(5);
	for (int i = 0; i < 5; i++)
		cout << (*new_enems[i]).getPriority() << '\t';
}
