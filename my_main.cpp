#include "VectorTester.hpp"
#include "StackTester.hpp"
#include "Bureaucrat.hpp"
#include <list>

#ifndef TESTED_NAMESPACE
# define TESTED_NAMESPACE ft
#endif

int main() {
	// std::cout << generateVal<Bureaucrat>(10) << std::endl;
	 testConstructors<int>("int");
}
