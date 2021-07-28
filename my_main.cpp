#include "VectorTester.hpp"
#include "StackTester.hpp"
#include "Bureaucrat.hpp"

int main() {
	ft::vector<int> intVector;
	const ft::vector<int> cIntVector = intVector;
	ft::vector<std::string> stringVector;
	ft::vector<Bureaucrat> bureaucratVector;
	{
		testFunctions<int>("Testing Int", intVector);
		stringTestFunctions("Testing std::string", stringVector);
		ft::vector<int>::const_iterator cIt = cIntVector.begin();
		for (; cIt != cIntVector.end(); cIt++)
			std::cout << *cIt << std::endl;
		testFunctions<Bureaucrat>("Testing Bureaucrat", bureaucratVector);
	}

//	ft::stack<int, ft::vector<int> > intStack;
//	ft::stack<std::string, ft::vector<std::string> > stringStack;
//	ft::stack<Bureaucrat, ft::vector<Bureaucrat> > bureaucratStack;
//	{
//		testStackFunctions<int, ft::stack<int, ft::vector<int> > >("Testing Int", intStack);
////		testStringStackFunctions<int>("Testing String", stringStack);
////		testStackFunctions<ft::stack<Bureaucrat, ft::vector<Bureaucrat> > >("Testing Bureaucrat", bureaucratStack);
//	}

}
