#include "VectorTester.hpp"
#include "StackTester.hpp"
#include "MapTester.hpp"
#include "SetTester.hpp"
#include "Timer.hpp"

int		main(void)
{
	Timer testVector;
	testConstructors<int>("Testing Vector");
	std::cout << std::string(STL) + "Testing Vector" << std::endl;
	testVector.getDiff();

	Timer testStack;
	testStackConstructors<int>("Testing Stack");
	std::cout << std::string(STL) + "Testing Stack" << std::endl;
	testVector.getDiff();

	Timer testMap;
	mapTestConstructors<int, int>("Testing Map");
	std::cout << std::string(STL) + "Testing Map" << std::endl;
	testMap.getDiff();

	Timer testSet;
	setTestConstructors<int>("Testing Set");
	std::cout << std::string(STL) + "Testing Set" << std::endl;
	testSet.getDiff();

	return (0);
}
