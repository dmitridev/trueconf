// trueconf.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <algorithm>
#include <iterator>
#include <map>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

ostream& operator<<(ostream& stream, vector<int> v);
ostream& operator<<(ostream& stream, map<int, int> m);

void deleteRandomNumbersForMap(map<int, int> &m);
void deleteRandomNumbersForVector(vector<int> &v);

void synchronize(vector<int> &v, map<int, int> &m);


int main()
{
	srand(time(NULL));
	vector<int> vecInt;
	map<int, int> mapInt;

	const size_t size = 20;
	
	for (int i = 0; i < size; i++) {
		vecInt.push_back(1+rand() % 9 );
		mapInt[i] = 1 + rand() % 9;
	}

	cout << vecInt << endl;
	cout << mapInt << endl;
	
	deleteRandomNumbersForMap(mapInt);
	deleteRandomNumbersForVector(vecInt);
	
	cout << string(80, '-').c_str();
	cout << "after random delete" << endl;
	

	cout << vecInt << endl;
	cout << mapInt << endl;

	cout << string(80, '-').c_str();

	cout << "synchronize map and vector" << endl;
	synchronize(vecInt, mapInt);

	cout << "after synchronize" << endl;
	cout << vecInt << endl;
	cout << mapInt << endl;

	getchar();

    return 0;
}

ostream& operator<<(ostream& stream, vector<int> v) {
	cout <<endl<< "vector has " << v.size() << " elements" << endl;
	for (int i = 0; i < v.size(); i++) {
		if (i % 10 == 0) cout << endl;
		cout <<setw(2) << v[i] << " ";
	}
	return stream;
}

ostream& operator<<(ostream& stream, map<int, int> m) {
	cout<<endl << "map has " << m.size() << " elements" << endl;
	int counter = 0;
	for(auto &i:m){
		if (counter %10 == 0) cout << endl;
		cout <<setw(2) << i.second << " ";
		counter++;
	}

	return stream;
}

void deleteRandomNumbersForMap(map<int, int> &m)
{
	int randomCount = (m.size() < 15) ?
		( 1 + rand() % m.size() ) 
		: (1 + rand() % 15);
	auto it = m.begin();
	for (int i = 0; i<randomCount; i++){
		it = m.find(i);
		it = m.erase(it);
	}
		

}

void deleteRandomNumbersForVector(vector<int> &v) {
	int randomCount = (v.size() < 15) ? 
		(1 + rand() % v.size()) 
		: (1 + rand() % 15);
	v.erase(v.begin(), v.begin() + randomCount);
}

void synchronize(vector<int>& v, map<int, int>& m){
	vector<int> numbersInBoth;

	copy_if(v.begin(), v.end(), back_inserter(numbersInBoth), [&m](const int&a) {
		for (auto&i : m)
			if (i.second == a)
				return true;

		return false;
	});

	sort(numbersInBoth.begin(), numbersInBoth.end());

	numbersInBoth.erase(
		unique(numbersInBoth.begin(), numbersInBoth.end()), 
		numbersInBoth.end());

	cout << "Unique elements are:" << endl;
	cout << string(80,'-').c_str();
	cout << numbersInBoth << endl;
	cout << string(80, '-').c_str();
	
	for (auto it = v.begin(); it != v.end();)
		if (find(numbersInBoth.begin(), 
			numbersInBoth.end(), 
			*it) == numbersInBoth.end())

			it = v.erase(it);

		else
			++it;
	
	for (auto it = m.begin(); it != m.end();)
		if (find(numbersInBoth.begin(), 
			numbersInBoth.end(), 
			it->second) == numbersInBoth.end())

			it = m.erase(it);

		else
	
			++it;
	
}
