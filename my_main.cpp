#include "VectorTester.hpp"
#include "Bureaucrat.hpp"

int main() {
	 ft::vector<int> vec0;
	 ft::vector<std::string> vec1;
	 {
	 	testFunctions<int>("Testing Int", vec0);
	 }
	 {
	 	stringTestFunctions<std::string>("Testing str", vec1);
	 }
	 {
	 	// testFunctions<Bureaucrat>("Testing Bureaucrat");
	 }
//	testConstructors<int>("testing int");
}
