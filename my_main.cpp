#include "VectorTester.hpp"
#include "StackTester.hpp"
#include "Bureaucrat.hpp"
#include <iostream>
//#include <list>
#include <stack>
//#include "common.hpp"
#include <map>
#include "map.hpp"

int main() {
	ft::map<int, int> mappa;

	ft::pair<ft::map<int, int>::iterator, bool> ret = mappa.insert(ft::make_pair(5, 32));
	mappa.insert(ft::make_pair(2, 32));
	mappa.insert(ft::make_pair(2, 32));
	mappa.insert(ft::make_pair(7, 32));
	mappa.insert(ft::make_pair(6, 32));
	mappa.insert(ft::make_pair(4, 32));
	mappa.insert(ft::make_pair(9, 32));

	ft::map<int, int>::iterator its = ret.first;
	std::cout << its->first << ret.first->first << std::endl;
	its++;
	its++;
	std::cout << its->first << std::endl;

//	std::cout << ret.first << std::endl;
//	ft::map<std::string, int>::iterator it = ret.first;
//	std::cout << it.first << std::endl;

//	std::cout << (mappa.insert(ft::make_pair(std::string("ciao"), 32)).first)->first << std::endl;
//	std::cout << mappa.insert(ft::make_pair(std::string("c45iao"), 32)).first->key.first << std::endl;
//	std::cout << mappa.insert(ft::make_pair(std::string("cia4o"), 32)).first->key.first << std::endl;
//	std::cout << mappa.insert(ft::make_pair(std::string("cia3o"), 32)).first->key.first << std::endl;
//	std::cout << mappa.insert(ft::make_pair(std::string("ci2ao"), 32)).first->key.first << std::endl;
//	std::map<std::string, int> mappa;
//
//	std::pair<std::map<std::string, int>::iterator, bool> ret = mappa.insert(std::make_pair(std::string("ciao"), 32));
//	std::map<std::string, int>::iterator it = ret.first;
//	std::cout << it->first << std::endl;

	return (0);
}
