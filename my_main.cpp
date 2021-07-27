#include "VectorTester.hpp"
#include "Bureaucrat.hpp"

int main() {
	{
		testFunctions<int>("Testing Int");
	}
	{
		stringTestFunctions("Testing std::string");
	}
	{
		testFunctions<Bureaucrat>("Testing Bureaucrat");
	}
}
