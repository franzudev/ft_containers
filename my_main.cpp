#include "VectorTester.hpp"
#include "StackTester.hpp"
#include "Bureaucrat.hpp"
#include <list>

#ifndef TESTED_NAMESPACE
# define TESTED_NAMESPACE ft
#endif

template <typename T>
void	printSize(TESTED_NAMESPACE::vector<T> const &vct, bool print_content = 1)
{
	std::cout << "size: " << vct.size() << std::endl;
	std::cout << "capacity: " << vct.capacity() << std::endl;
	std::cout << "max_size: " << vct.max_size() << std::endl;
	if (print_content)
	{
		typename TESTED_NAMESPACE::vector<T>::const_iterator it = vct.begin();
		typename TESTED_NAMESPACE::vector<T>::const_iterator ite = vct.end();
		std::cout << std::endl << "Content is:" << std::endl;
		for (; it != ite; ++it)
		{
			std::cout << "- " << *it << std::endl;
		}
	}
	std::cout << "###############################################" << std::endl;
}

class foo {
	public:
		foo(void) { };
		~foo(void) { };
		void m(void) { std::cout << "foo::m called [" << this->value << "]" << std::endl; };
		void m(void) const { std::cout << "foo::m const called [" << this->value << "]" << std::endl; };
		foo &operator=(int src) { this->value = src; return *this; };
		int getValue(void) const { return this->value; };
	private:
		int	value;
};

std::ostream	&operator<<(std::ostream &o, foo const &bar) {
	o << bar.getValue();
	return o;
}

int main() {
	// ft::vector<int> intVector;
	// const ft::vector<int> cIntVector = intVector;
	// ft::vector<std::string> stringVector;
	// ft::vector<Bureaucrat> bureaucratVector;
	// {
	// 	testFunctions<int>("Testing Int", intVector);
	// 	stringTestFunctions("Testing std::string", stringVector);
	// 	ft::vector<int>::const_iterator cIt = cIntVector.begin();
	// 	for (; cIt != cIntVector.end(); cIt++)
	// 		std::cout << *cIt << std::endl;
	// 	testFunctions<Bureaucrat>("Testing Bureaucrat", bureaucratVector);
	// }



//	ft::stack<int, ft::vector<int> > intStack;
//	ft::stack<std::string, ft::vector<std::string> > stringStack;
//	ft::stack<Bureaucrat, ft::vector<Bureaucrat> > bureaucratStack;
//	{
//		testStackFunctions<int, ft::stack<int, ft::vector<int> > >("Testing Int", intStack);
////		testStringStackFunctions<int>("Testing String", stringStack);
////		testStackFunctions<ft::stack<Bureaucrat, ft::vector<Bureaucrat> > >("Testing Bureaucrat", bureaucratStack);
//	}

	// std::list<int> lst;
	// std::list<int>::iterator lst_it;
	// for (int i = 1; i < 5; ++i)
	// 	lst.push_back(i * 3);

	// ft::vector<int> vct(lst.begin(), lst.end());
	// // printSize(vct);

	// lst_it = lst.begin();
	// std::cout << "banana" << std::endl;
	// // for (int i = 1; lst_it != lst.end(); ++i)
	// // {
	// // 	std::cout << "banana" << std::endl;
	// // 	*lst_it++ = i * 5;
	// // 	lst_it++;
	// // }
	// vct.assign(lst.begin(), lst.end());
	// // printSize(vct);

	// vct.insert(vct.end(), lst.rbegin(), lst.rend());
	// // printSize(vct);
	// return (0);
	// std::string a(1);
	// testConstructors<int>("int");
	testConstructors<std::string>("String");
	// testConstructors<std::string>("string");
}
