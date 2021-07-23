//
// Created by Federico Francois on 7/19/21.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <iterator>
#include "Bureaucrat.hpp"
#include "iterator.hpp"
#include "vector.hpp"

template <class T>
void	testerfunction() {

}

int main() {

	// char
	/*{
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
	}*/
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
		ft::vector<int> rvect;
		rvect.push_back(10);
		rvect.push_back(20);
		rvect.push_back(40);
		rvect.push_back(50);
		g.assign(100, 10);
		for (ft::vector<int>::iterator start = g.begin(); start != g.end(); ++start)
			std::cout << "val : " << *start << std::endl;
		g.assign(rvect.begin(), rvect.end());
		for (ft::vector<int>::iterator start = g.begin(); start != g.end(); ++start)
			std::cout << "val : " << *start << std::endl;
		std::cout << "pop" << std::endl;
		g.pop_back();


		ft::vector<int>::iterator twenty = g.begin();
		twenty++;
		twenty++;
		g.insert(twenty, 15);
		ft::vector<int>::iterator fifteen = g.begin();
		g.insert(fifteen, 15);
		ft::vector<int>::iterator fift = g.begin();
		g.insert(fift, 15);
		ft::vector<int>::iterator sixt = g.begin();
		ft::vector<int> cvect;
		cvect.push_back(1000);
		cvect.push_back(2000);
		cvect.push_back(3000);
		cvect.push_back(4000);
		cvect.push_back(5000);
		cvect.push_back(6000);
		cvect.push_back(7000);
		cvect.push_back(8000);
		g.insert(sixt, cvect.begin(), cvect.end());
		ft::vector<int>::iterator iast = g.begin();
		ft::vector<int>::iterator prova = g.erase((g.begin()));
		g.erase(prova, prova + 3);
		g.swap(cvect);
		cvect.clear();
		for (ft::vector<int>::iterator start = cvect.begin(); start != cvect.end(); start++)
			std::cout << "val : " << *start << std::endl;
		std::cout << (g == cvect) << std::endl;
//		std::cout << *prova << std::endl;
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
	/*{
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
		std::cout << " ***** Postfix operators reverse ***** " << std::endl;
		std::cout << "rit++: " << *(rit++) << std::endl;
		std::cout << "rit  : " << *rit << std::endl;
		std::cout << "--rit: " << *(--rit) << std::endl;
		std::cout << "++rit: " << *(++rit) << std::endl;
		std::cout << "rit--: " << *(rit--) << std::endl;
		std::cout << "rit  : " << *rit << std::endl;

		std::cout << std::endl << std::endl;
		std::cout << " ***** Vector accessors ***** " << std::endl;
		std::cout << "operator[]" << std::endl;
		std::cout << "Gianni == " << g[5] << std::endl;
		std::cout << "Pinotto == " << g[1] << std::endl;
		std::cout << "at()" << std::endl;
		std::cout << "Gianni == " << g.at(0) << std::endl;
		std::cout << "Pinotto == " << g.at(1) << std::endl;
		try {
			std::cout << "Out of range == " << g.at(235) << std::endl;
		} catch (std::exception &e){
			std::cout << e.what() << std::endl << std::endl;
		}
		std::cout << "front()" << std::endl;
		std::cout << "Gianni == " << g.front() << std::endl;
		std::cout << "back()" << std::endl;
		std::cout << "Pinotto == " << g.back() << std::endl;
		std::cout << std::endl << std::endl;


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
	}*/
}
