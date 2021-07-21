//
// Created by Federico Francois on 7/19/21.
//

#include <iostream>
#include <vector>
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
	std::vector<char> h;
	g.push_back('a');
	std::cout << g.size() << std::endl;
	g.push_back('b');
	std::cout << g.size() << std::endl;
	h.push_back('a');
	h.push_back('b');
	ft::vector<char>::iterator it = g.begin();
//	std::vector<char>::iterator it2 = h.begin();

	std::cout << *it << '\n';
	*it = *(++it);
	std::cout << *it << '\n';
}
