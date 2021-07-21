//
// Created by Federico Francois on 7/19/21.
//

#include <iostream>
#include <vector>
//#include <algorithm>
#include "iterator.hpp"
#include "vector.hpp"
int main() {

	// char
	{
		std::cout << " ************* Testing char ************* " << std::endl;
		ft::vector<char> g;
		g.push_back('a');
		std::cout << "Size: " << g.size() << std::endl;
		g.push_back('b');
		std::cout << "Size: " << g.size() << std::endl;
		ft::vector<char>::iterator it = g.begin();

		for (ft::vector<char>::iterator start = it; start != g.end(); ++start){
			std::cout << "val : " << *start << std::endl;
		}
		g.push_back('t');
		for (ft::vector<char>::iterator start = it; start != g.end(); ++start)
			std::cout << "val : " << *start << std::endl;
	}
	// int
	{
		std::cout << " ************* Testing int ************* " << std::endl;
		ft::vector<int> g;
		g.push_back(1);
		std::cout << "Size: " << g.size() << std::endl;
		g.push_back(10);
		std::cout << "Size: " << g.size() << std::endl;
		ft::vector<int>::iterator it = g.begin();

		for (ft::vector<int>::iterator start = it; start != g.end(); ++start){
			std::cout << "val : " << *start << std::endl;
		}
		g.push_back(100);
		for (ft::vector<int>::iterator start = it; start != g.end(); ++start)
			std::cout << "val : " << *start << std::endl;
	}

	// std::string
	{
		std::cout << " ************* Testing std::string ************* " << std::endl;
		ft::vector<std::string> g;
		g.push_back("Ciao");
		std::cout << "Size: " << g.size() << std::endl;
		g.push_back("Programmatori");
		std::cout << "Size: " << g.size() << std::endl;
		ft::vector<std::string>::iterator it = g.begin();

		for (ft::vector<std::string>::iterator start = it; start != g.end(); ++start){
			std::cout << "val : " << *start << std::endl;
		}
		g.push_back("del cazzo!");
		for (ft::vector<std::string>::iterator start = it; start != g.end(); ++start)
			std::cout << "val : " << *start << std::endl;
	}

}
