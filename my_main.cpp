//
// Created by Federico Francois on 7/19/21.
//

#include <iostream>
#include <vector>
//#include <algorithm>
#include "iterator.hpp"
#include "vector.hpp"
int main() {
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
