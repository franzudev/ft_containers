#include "common.hpp"
#include <list>

#define T1 int
#define T2 int
typedef _pair<const T1, T2> T3;

int		main(void)
{
	ft::map<std::string, int> mp;

	mp.insert(ft::make_pair<std::string, int>("toro", 5));
	mp.insert(ft::make_pair<std::string, int>("toro1", 5));
	mp.insert(ft::make_pair<std::string, int>("toro2", 5));
	mp.insert(ft::make_pair<std::string, int>("toro3", 5));

	std::cout << mp.find("toro")->second << std::endl;
	std::cout << mp.count("toro") << mp.count("torone") << std::endl;

	try {
		std::cout << mp.at("toro") << std::endl;
	} catch (std::exception &e) {
		std::cout << e.what() << std::endl;
	}
	return (0);
}
