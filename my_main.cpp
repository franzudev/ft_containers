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
#include <list>

#define T1 int
#define T2 foo<int>
typedef TESTED_NAMESPACE::map<T1, T2>::value_type T3;
typedef TESTED_NAMESPACE::map<T1, T2>::iterator ft_iterator;
typedef TESTED_NAMESPACE::map<T1, T2>::const_iterator ft_const_iterator;

static int iter = 0;

template <typename MAP>
void	ft_bound(MAP &mp, const T1 &param)
{
	ft_iterator ite = mp.end(), it[2];
	// _pair<ft_iterator, ft_iterator> ft_range;

	std::cout << "\t-- [" << iter++ << "] --" << std::endl;
	std::cout << "with key [" << param << "]:" << std::endl;
	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
	// ft_range = mp.equal_range(param);
	std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(it[0], false)) << std::endl;
	std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(it[1], false)) << std::endl;
	// std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
}

template <typename MAP>
void	ft_const_bound(const MAP &mp, const T1 &param)
{
	ft_const_iterator ite = mp.end(), it[2];
	// _pair<ft_const_iterator, ft_const_iterator> ft_range;

	std::cout << "\t-- [" << iter++ << "] (const) --" << std::endl;
	std::cout << "with key [" << param << "]:" << std::endl;
	it[0] = mp.lower_bound(param); it[1] = mp.upper_bound(param);
	// ft_range = mp.equal_range(param);
	std::cout << "lower_bound: " << (it[0] == ite ? "end()" : printPair(it[0], false)) << std::endl;
	std::cout << "upper_bound: " << (it[1] == ite ? "end()" : printPair(it[1], false)) << std::endl;
	// std::cout << "equal_range: " << (ft_range.first == it[0] && ft_range.second == it[1]) << std::endl;
}

int		main(void)
{
	std::list<T3> lst;
	unsigned int lst_size = 10;
	for (unsigned int i = 0; i < lst_size; ++i)
		lst.push_back(T3(i + 1, (i + 1) * 3));
	TESTED_NAMESPACE::map<T1, T2> mp(lst.begin(), lst.end());
	printSize(mp);

	ft_const_bound(mp, -10);
	ft_const_bound(mp, 1);
	ft_const_bound(mp, 5);
	ft_const_bound(mp, 10);
	ft_const_bound(mp, 50);

	printSize(mp);

	mp.lower_bound(3)->second = 404;
	mp.upper_bound(7)->second = 842;
	ft_bound(mp, 5);
	ft_bound(mp, 7);

	printSize(mp);
	return (0);
}
