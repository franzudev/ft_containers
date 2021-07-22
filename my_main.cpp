//
// Created by Federico Francois on 7/19/21.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include "Bureaucrat.hpp"
#include "iterator.hpp"
#include "vector.hpp"

template <class T>
void	testerfunction() {

}

int main() {

	// char
	{
		std::cout << " ************* Testing char ************* " << std::endl;
		ft::vector<char> g;
		char a = 'a', b = 'b', c = 't';
		std::cout << "Push: char(" << a << ")" << std::endl;
		g.push_back(a);
		std::cout << "Size: " << g.size() << std::endl;
		std::cout << "Push: char(" << b << ")" << std::endl;
		g.push_back(b);
		std::cout << "Size: " << g.size() << std::endl;
		ft::vector<char>::iterator it = g.begin();

		std::cout << std::endl << std::endl;
		std::cout << " ***** Postfix operators ***** " << std::endl;
		std::cout << "it++: " << *(it++) << std::endl << std::endl;
		std::cout << "it  : " << *it << std::endl << std::endl;
		std::cout << "--it: " << *(--it) << std::endl << std::endl;
		std::cout << "++it: " << *(++it) << std::endl << std::endl;
		std::cout << "it--: " << *(it--) << std::endl << std::endl;
		std::cout << "it  : " << *it << std::endl << std::endl;

		for (ft::vector<char>::iterator start = g.begin(); start != g.end(); ++start){
			std::cout << "val : " << *start << std::endl;
		}
		std::cout << "Push: int(" << c << ")" << std::endl;
		g.push_back(c);
		for (ft::vector<char>::iterator start = g.begin(); start != g.end(); ++start)
			std::cout << "val : " << *start << std::endl;
		std::cout << "Resizing: " << std::endl;
		g.resize(1);
		for (ft::vector<char>::iterator start = g.begin(); start != g.end(); ++start)
			std::cout << "val : " << *start << std::endl;
		std::cout << std::endl;
	}
	// int
	{
		std::cout << " ************* Testing int ************* " << std::endl;
		ft::vector<int> g;
		int a = 1, b = 10, c = 100;
		std::cout << "Push: int(" << a << ")" << std::endl;
		g.push_back(a);
		std::cout << "Size: " << g.size() << std::endl;
		std::cout << "Push: int(" << b << ")" << std::endl;
		g.push_back(b);
		std::cout << "Size: " << g.size() << std::endl;
		ft::vector<int>::iterator it = g.begin();

		std::cout << std::endl << std::endl;
		std::cout << " ***** Postfix operators ***** " << std::endl;
		std::cout << "it++: " << *(it++) << std::endl << std::endl;
		std::cout << "it  : " << *it << std::endl << std::endl;
		std::cout << "--it: " << *(--it) << std::endl << std::endl;
		std::cout << "++it: " << *(++it) << std::endl << std::endl;
		std::cout << "it--: " << *(it--) << std::endl << std::endl;
		std::cout << "it  : " << *it << std::endl << std::endl;

		for (ft::vector<int>::iterator start = g.begin(); start != g.end(); ++start){
			std::cout << "val : " << *start << std::endl;
		}
		std::cout << "Push: int(" << c << ")" << std::endl;
		g.push_back(c);
		for (ft::vector<int>::iterator start = it; start != g.end(); ++start)
			std::cout << "val : " << *start << std::endl;

		std::cout << "  Resizing: " << std::endl;
		g.resize(1);
		for (ft::vector<int>::iterator start = g.begin(); start != g.end(); ++start)
			std::cout << "val : " << *start << std::endl;
		std::cout << std::endl;
	}

	// std::string
	/*{
		std::cout << " ************* Testing std::string ************* " << std::endl;
		ft::vector<std::string> g;
		std::string a = "Ciao", b = "Programmatori", c = "fannulloni";
		std::cout << "Push: std::string(\"" << a << "\")" << std::endl;
		g.push_back(a);
		std::cout << "Size: " << g.size() << std::endl;
		std::cout << "Push: std::string(\"" << b << "\")" << std::endl;
		g.push_back(b);
		std::cout << "Size: " << g.size() << std::endl;
		ft::vector<std::string>::iterator it = g.begin();

		std::cout << std::endl << std::endl;
		std::cout << " ***** Postfix operators ***** " << std::endl << std::endl;
		std::cout << "it++: " << *(it++) << std::endl << std::endl;
		std::cout << "it  : " << *it << std::endl << std::endl;
		std::cout << "--it: " << *(--it) << std::endl << std::endl;
		std::cout << "++it: " << *(++it) << std::endl << std::endl;
		std::cout << "it--: " << *(it--) << std::endl << std::endl;
		std::cout << "it  : " << *it << std::endl << std::endl;

		for (ft::vector<std::string>::iterator start = g.begin(); start != g.end(); ++start){
			std::cout << "val : " << *start << std::endl;
		}
		std::cout << "Push: std::string(\"" << c << "\")" << std::endl;
		g.push_back(c);
		for (ft::vector<std::string>::iterator start = g.begin(); start != g.end(); ++start)
			std::cout << "val : " << *start << std::endl;

		std::cout << "  Resizing: " << std::endl;
		g.resize(1);
		for (ft::vector<std::string>::iterator start = g.begin(); start != g.end(); ++start)
			std::cout << "val : " << *start << std::endl;
		std::cout << std::endl;
	}*/
	// Bureaucreat
	{
		std::cout << " ************* Testing Bureaucrat ************* " << std::endl;
		ft::vector<Bureaucrat> g;
		std::string a = "Gianni", b = "Pinotto", c = "Non lo so";
		std::cout << "Push: Bureaucrat(\"" << a << "\", 14500)" << std::endl;
		g.push_back(Bureaucrat(a, 14500));
		std::cout << "Size: " << g.size() << std::endl;
		std::cout << "Push: Bureaucrat(\"" << b << "\", 32555)" << std::endl;
		g.push_back(Bureaucrat(b, 32555));
		std::cout << "Size: " << g.size() << std::endl;
		ft::vector<Bureaucrat>::iterator it = g.begin();

		std::cout << std::endl << std::endl;
		std::cout << " ***** Postfix operators ***** " << std::endl;
		std::cout << "it++: " << *(it++) << std::endl;
		std::cout << "it  : " << *it << std::endl;
		std::cout << "--it: " << *(--it) << std::endl;
		std::cout << "++it: " << *(++it) << std::endl;
		std::cout << "it--: " << *(it--) << std::endl;
		std::cout << "it  : " << *it << std::endl;
		ft::vector<Bureaucrat>::reverse_iterator rit = g.rbegin();

		std::cout << std::endl << std::endl;
		std::cout << " ***** Postfix operators ***** " << std::endl;
		std::cout << "rit++: " << *(rit++) << std::endl;
		std::cout << "rit  : " << *rit << std::endl;
		std::cout << "--rit: " << *(--rit) << std::endl;
		std::cout << "++rit: " << *(++rit) << std::endl;
		std::cout << "rit--: " << *(rit--) << std::endl;
		std::cout << "rit  : " << *rit << std::endl;

		for (ft::vector<Bureaucrat>::iterator start = g.begin(); start != g.end(); start++){
			std::cout << *start << std::endl;
		}
		std::cout << "Push: Bureaucrat(\"" << c << "\", 32555)" << std::endl;
		g.push_back(Bureaucrat(c, 3423));
		for (ft::vector<Bureaucrat>::iterator start = g.begin(); start != g.end(); start++)
			std::cout << *start << std::endl;
//		to try
		std::cout << std::endl << std::endl;
		std::cout << " Reverse iterators" << std::endl;
		for (ft::vector<Bureaucrat>::reverse_iterator start = g.rbegin(); start != g.rend(); start++)
			std::cout << *start << std::endl;
		std::cout << std::endl << std::endl;
		std::cout << "  Resizing: " << std::endl;
		g.resize(1);
		for (ft::vector<Bureaucrat>::iterator start = g.begin(); start != g.end(); start++)
			std::cout << *start << std::endl;
		std::cout << std::endl;
	}

}
