// #include "common.hpp"
// #include <list>

// #define T1 char
// #define T2 int
// typedef _pair<const T1, T2> T3;

// int main (void)
// {
// 	std::list<T3> lst;

// 	unsigned int lst_size = 7;
// 	for (unsigned int i = 0; i < lst_size; ++i)
// 		lst.push_back(T3('a' + i, lst_size - i));
// 	TESTED_NAMESPACE::map<T1, T2> foo(lst.begin(), lst.end());

// 	lst.clear(); lst_size = 4;
// 	for (unsigned int i = 0; i < lst_size; ++i)
// 		lst.push_back(T3('z' - i, i * 5));
// 	TESTED_NAMESPACE::map<T1, T2> bar(lst.begin(), lst.end());

// 	TESTED_NAMESPACE::map<T1, T2>::const_iterator it_foo = foo.begin();
// 	TESTED_NAMESPACE::map<T1, T2>::const_iterator it_bar = bar.begin();

// 	std::cout << "BEFORE SWAP" << std::endl;

// 	std::cout << "foo contains:" << std::endl;
// 	printSize(foo);
// 	std::cout << "bar contains:" << std::endl;
// 	printSize(bar);

// 	foo.swap(bar);

// 	std::cout << "AFTER SWAP" << std::endl;

// 	std::cout << "foo contains:" << std::endl;
// 	printSize(foo);
// 	std::cout << "bar contains:" << std::endl;
// 	printSize(bar);

// 	std::cout << "Iterator validity:" << std::endl;
// 	std::cout << (it_foo == bar.begin()) << std::endl;
// 	std::cout << (it_bar == foo.begin()) << std::endl;

// 	return (0);
// }


//================

#include "common.hpp"
#include "Timer.hpp"

#define T1 int
#define T2 std::string
typedef TESTED_NAMESPACE::map<T1, T2>::value_type T3;
typedef TESTED_NAMESPACE::map<T1, T2>::iterator iterator;

static int iter = 0;

template <typename MAP, typename U>
void	ft_insert(MAP &mp, U param)
{
	_pair<iterator, bool> tmp;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	tmp = mp.insert(param);
	std::cout << "insert return: " << printPair(tmp.first);
	std::cout << "Created new node: " << tmp.second << std::endl;
	printSize(mp);
}

template <typename MAP, typename U, typename V>
void	ft_insert(MAP &mp, U param, V param2)
{
	iterator tmp;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	tmp = mp.insert(param, param2);
	std::cout << "insert return: " << printPair(tmp);
	printSize(mp);
}

int		main(void)
{
	Timer test;
	TESTED_NAMESPACE::map<T1, T2> mp, mp2;

	ft_insert(mp, T3(42, "lol"));
	ft_insert(mp, T3(42, "mdr"));

	ft_insert(mp, T3(50, "mdr"));
	ft_insert(mp, T3(35, "funny"));

	ft_insert(mp, T3(45, "bunny"));
	ft_insert(mp, T3(21, "fizz"));
	ft_insert(mp, T3(38, "buzz"));

	ft_insert(mp, mp.begin(), T3(55, "fuzzy"));

	ft_insert(mp2, mp2.begin(), T3(1337, "beauty"));
	ft_insert(mp2, mp2.end(), T3(1000, "Hello"));
	ft_insert(mp2, mp2.end(), T3(1500, "World"));
	test.getDiff();
	return (0);
}
