#include "VectorTester.hpp"
#include "StackTester.hpp"
#include "Bureaucrat.hpp"

int main() {
//	ft::vector<int> intVector;
//	ft::vector<std::string> stringVector;
//	ft::vector<Bureaucrat> bureaucratVector;
//	{
//		testFunctions<int>("Testing Int", intVector);
//		stringTestFunctions("Testing std::string", stringVector);
//		testFunctions<Bureaucrat>("Testing Bureaucrat", bureaucratVector);
//	}

	ft::stack<int, ft::vector<int> > intStack;
	ft::stack<std::string, ft::vector<std::string> > stringStack;
	ft::stack<Bureaucrat, ft::vector<Bureaucrat> > bureaucratStack;
	{
		testStackFunctions<int, ft::stack<int, ft::vector<int> > >("Testing Int", intStack);
//		testStringStackFunctions<int>("Testing String", stringStack);
//		testStackFunctions<ft::stack<Bureaucrat, ft::vector<Bureaucrat> > >("Testing Bureaucrat", bureaucratStack);
	}

}
