//
// Created by Federico Francois on 7/19/21.
//

#include <iostream>
//#include <vector>
//#include <algorithm>
#include "iterator.hpp"
#include "vector.hpp"
int main() {
//	ft::vector<int> pippo;
//	for (int i = 0; i < 10; ++i)
//		pippo.push_back(i);
//
//	for (
//			ft::vector<int>::iterator \
//				gino = pippo.begin(), \
//				nino = pippo.end();
//			nino != gino ;
//			++gino)
//	{
//		std::cout << *gino << ' ';
//	}
//	return 0;
	ft::vector<char> g;
	g.push_back('a');
	g.push_back('b');
	ft::vector<char>::iterator it = g.begin();
	ft::vector<char>::iterator it2 = it - 100000;
	if (it2 == it)
		std::cout << "pippo\n";
	std::cout << &(it) << '\n' << &(it2) << '\n';
}
