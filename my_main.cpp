#include "VectorTester.hpp"
#include "SetTester.hpp"
#include "Timer.hpp"

int		main(void)
{
	Timer testVector;
	testConstructors<int>("Testing Vector");
	testVector.getDiff();

	Timer testSet;
	setTestConstructors<int>("Testing Set");
	testSet.getDiff();

	return (0);
}
