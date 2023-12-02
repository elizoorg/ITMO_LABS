#include <iostream>
#include <algorithm>
#include <vector>
#include "Array.h"
using namespace std;
#ifdef DEBUG 

#endif


int main() {
	Array<int> array = { 1, 2, 3, 4, 5 };
	
	cout << array << endl;
	array.insert(1);
	cout << array << endl;
	array.insert(2);
	cout << array << endl;
	array.insert(3);
	cout << array << endl;
	array.insert(4);
	cout << array << endl;
	array.insert(5);
	cout << array << endl;
	
	auto itr = std::find(array.begin(), array.end(), 5);
	auto itr1 = std::find(array.begin(), array.end(), 17);
	cout << *itr << ' ' << *itr1 << endl;
	cout << array << endl;
	array.insert(6);
	cout << array << endl;
	array.remove(1);
	cout << array << endl;
	array.remove(2);
	cout << array << endl;
	array.size();
	cout << array << endl;
	Array<int> a;
	for (int i = 0; i < 10; ++i) a.insert(i + 1);

	for (int i = 0; i < a.size(); ++i) a[i] *= 2;

	for (auto it = a.reverseIterator(); it.hasNext(); it.next()) { std::cout << it.get() << std::endl; }


	for (auto &elt : a)
		std::cout << elt << " " << endl;
		std::cout << std::endl;
		std::cout << std::distance(a.iterator(), a.reverseIterator()) << std::endl;
		

	return 0;
}

