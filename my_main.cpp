#include "VectorTester.hpp"
#include "Bureaucrat.hpp"

int main() {
	ft::vector<int> intVector;
	ft::vector<std::string> stringVector;
	ft::vector<Bureaucrat> bureaucratVector;
	{
		testFunctions<int>("Testing Int", intVector);
	}
	{
		stringTestFunctions("Testing std::string", stringVector);
	}
	{
		testFunctions<Bureaucrat>("Testing Bureaucrat", bureaucratVector);
	}
}
