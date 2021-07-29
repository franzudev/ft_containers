#include "VectorTester.hpp"
#include "StackTester.hpp"
#include "Bureaucrat.hpp"
#include <list>

#ifndef TESTED_NAMESPACE
# define TESTED_NAMESPACE ft
#endif

int main() {
	ft::vector<int> intVector;
	const ft::vector<int> cIntVector = intVector;
	ft::vector<std::string> stringVector;
	ft::vector<Bureaucrat> bureaucratVector;
	testFunctions<int>("Testing Int", intVector);
//	stringTestFunctions("Testing ft::string", stringVector);
	ft::vector<int>::const_iterator cIt = cIntVector.begin();
	for (; cIt != cIntVector.end(); cIt++)
		std::cout << *cIt << std::endl;
	testFunctions<Bureaucrat>("Testing Bureaucrat", bureaucratVector);

//	ft::vector<int> test2;
//	test2.push_back(1);
//	intVector.swap(test2);
//	std::cout << intVector[0] << std::endl;
//	ft::swap(intVector, test2);
//	std::cout << intVector[0];
//
//	{
//		ft::stack<int, ft::vector<int> > intStack;
////		ft::stack<Bureaucrat, ft::vector<Bureaucrat> > bureaucratStack;
//		for (size_t i = 0; i < TEST_ARR_SIZE; i++)
//			intStack.push(generateVal<int>(i));
//		{
//			testStackFunctions<int, ft::vector<int> >("Testing Int", intStack);
////			testStackFunctions<Bureaucrat, ft::vector<Bureaucrat> >("Testing Bureaucrat", bureaucratStack);
//		}
//	}
}
