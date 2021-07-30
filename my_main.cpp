//#include "VectorTester.hpp"
//#include "StackTester.hpp"
//#include "Bureaucrat.hpp"
#include <iostream>
#include <list>
#include "common.hpp"



#define TESTED_TYPE int

//int main() {
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
//	return (0);
//}
/*void	prepost_incdec(TESTED_NAMESPACE::vector<TESTED_TYPE> &vct)
{
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = vct.begin();
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it_tmp;

	std::cout << "Pre inc" << std::endl;
	it_tmp = ++it;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Pre dec" << std::endl;
	it_tmp = --it;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Post inc" << std::endl;
	it_tmp = it++;
	std::cout << *it_tmp << " | " << *it << std::endl;

	std::cout << "Post dec" << std::endl;
	it_tmp = it--;
	std::cout << *it_tmp << " | " << *it << std::endl;
	std::cout << "###############################################" << std::endl;
}

int		main(void)
{
	const int size = 5;
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(size);
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it = vct.begin();
	TESTED_NAMESPACE::vector<TESTED_TYPE>::const_iterator ite = vct.begin();

	for (int i = 0; i < size; ++i)
		it[i] = (size - i) * 5;
	prepost_incdec(vct);

	it = it + 5;
	it = 1 + it;
	it = it - 4;
	std::cout << *(it += 2) << std::endl;
	std::cout << *(it -= 1) << std::endl;

	*(it -= 2) = 42;
	*(it += 2) = 21;

	std::cout << "const_ite +=: " << *(ite += 2) << std::endl;
	std::cout << "const_ite -=: " << *(ite -= 2) << std::endl;

	std::cout << "(it == const_it): " << (ite == it) << std::endl;
	std::cout << "(const_ite - it): " << (ite - it) << std::endl;
	std::cout << "(ite + 3 == it): " << (ite + 3 == it) << std::endl;

	printSize(vct, true);
	return (0);
}
*/

int		main(void)
{
	const int size = 5;
	TESTED_NAMESPACE::vector<TESTED_TYPE> vct(size);
	TESTED_NAMESPACE::vector<TESTED_TYPE>::iterator it_ = vct.begin();
	TESTED_NAMESPACE::vector<TESTED_TYPE>::reverse_iterator it(it_);

	for (int i = 0; i < size; ++i)
		vct[i] = (i + 1) * 5;
	printSize(vct);

	std::cout << (it_ == it.base()) << std::endl;
	std::cout << (it_ == (it + 3).base()) << std::endl;

	std::cout << *(it.base() + 1) << std::endl;
	std::cout << *(it - 3) << std::endl;
	std::cout << *(it - 3).base() << std::endl;
	it -= 3;
	std::cout << *it.base() << std::endl;

	std::cout << "TEST OFFSET" << std::endl;
	std::cout << *(it) << std::endl;
	std::cout << *(it).base() << std::endl;
	std::cout << *(it - 0) << std::endl;
	std::cout << *(it - 0).base() << std::endl;
	std::cout << *(it - 1).base() << std::endl;

	return (0);
}
