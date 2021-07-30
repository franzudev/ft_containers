#include "VectorTester.hpp"
#include "StackTester.hpp"
#include "Bureaucrat.hpp"
#include <list>

#ifndef ft
# define ft ft
#endif

int main() {
//	ft::vector<int> intVector;
//	const ft::vector<int> cIntVector = intVector;
//	ft::vector<std::string> stringVector;
//	ft::vector<Bureaucrat> bureaucratVector;
//	testFunctions<int>("Testing Int", intVector);
//	stringTestFunctions("Testing ft::string", stringVector);
//	ft::vector<int>::const_iterator cIt = cIntVector.begin();
//	for (; cIt != cIntVector.end(); cIt++)
//		std::cout << *cIt << std::endl;
//	testFunctions<Bureaucrat>("Testing Bureaucrat", bureaucratVector);

	//leaked
//	ft::vector<int> test2;
//	test2.push_back(1);
//	intVector.swap(test2);
//	std::cout << intVector[0] << std::endl;
//	ft::swap(intVector, test2);
//	std::cout << intVector[0];

//	{
//		ft::stack<int, ft::vector<int> > intStack;
////		ft::stack<Bureaucrat, ft::vector<Bureaucrat> > bureaucratStack;
//		for (size_t i = 0; i < TEST_ARR_SIZE; i++)
//			intStack.push(i);
//		{
//			testStackFunctions<int, ft::vector<int> >("Testing Int", intStack);
////			testStackFunctions<Bureaucrat, ft::vector<Bureaucrat> >("Testing Bureaucrat", bureaucratStack);
//		}
////		ft::vector<int> zio;
//	}

	std::list<int> lst;
	std::list<int>::iterator lst_it;
	for (int i = 1; i < 5; ++i)
		lst.push_back(i * 3);

	ft::vector<int> vct(lst.begin(), lst.end());

	lst_it = lst.begin();
	for (int i = 1; lst_it != lst.end(); ++i)
		*lst_it++ = i * 5;
	vct.assign(lst.begin(), lst.end());

	vct.insert(vct.end(), lst.rbegin(), lst.rend());
	return (0);
}
