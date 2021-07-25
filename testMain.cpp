#include <iostream>
#include <vector>
#include <algorithm>
#include <array>
#include <iterator>
#include "iterator.hpp"
#include "vector.hpp"
#include <chrono>

// namespace ft=std;
using std::cout;
using std::endl;

#define P(x) cout << x << endl

template <typename vecType>
void	printVec(ft::vector<vecType> &vec)
{
	// (void)vec;
	P("size: " << vec.size() << " capacity: " << vec.capacity() << " max_size: " << vec.max_size() << " empty: " << vec.empty());
}

template <typename vecType>
void	printValuesOf(ft::vector<vecType> &vec)
{
	typename ft::vector<vecType>::iterator end = vec.end();
	if (vec.empty())
	{
		P("Vector is empty");
		return ;
	}
	for (typename ft::vector<vecType>::iterator beg = vec.begin(); beg != end; beg++)
	{
		std::cout << *beg;
		if (beg + 1 != end)
			std::cout << ", ";
	}
	std::cout << std::endl;
}

// template <typename vecType>
// void	testVecOfType
// {

// }

template<typename type>
type	generateVal(int index)
{
	(void)index;
	return (0);
}

template <>
int		generateVal<int>(int index)
{
	return (index);
}

template <>
char	generateVal<char>(int index)
{
	char ret[10] = {'c', 'i', 'a', 'o', 'b', 'a', 'n', 'a', 'n', 'a'};
	return (ret[index % 10]);
}

template <>
size_t	generateVal<size_t>(int index)
{
	return (static_cast<size_t>(index));
}

template<>
std::string	generateVal<std::string>(int index)
{
	std::string arr[8] = {"ciao", "come", "va", "li", "a", "milano", "in", "bocconi"};
	return(arr[index % 8]);
}

template<typename type>
void	vecConstructorsTest()
{
	P("Default constructor");
	ft::vector<type>		vec1;
	P("vec1:");
	printVec<type>(vec1);
	P("Size constructor");
	ft::vector<type>		vec2(10);
	P("vec2:");
	printVec<type>(vec2);
	// WIP
	// std::vector<type>		vecToCopy;
	// vecToCopy.insert(vecToCopy.begin(), 50, generateVal<type>(1));
	// P("Range Constructor");
	// WIP it does not work using ft, to make this work i had to change the insert function in our lib, to check ASAP ... does not work at all
	// ft::vector<type>		vec3(vecToCopy.begin(), vecToCopy.end());
	// printVec(vec3);
}

template<typename type>
void	vecPushPopTest()
{
	P("Push");
	ft::vector<type>		vec3;
	vec3.push_back(generateVal<type>(1));
	vec3.push_back(generateVal<type>(2));
	vec3.push_back(generateVal<type>(3));
	printVec<type>(vec3);
	printValuesOf<type>(vec3);
	P("Pop");
	vec3.pop_back();
	vec3.pop_back();
	vec3.pop_back();
	printVec<type>(vec3);
	printValuesOf<type>(vec3);
	vec3.push_back(generateVal<type>(4));
	printVec<type>(vec3);
	printValuesOf<type>(vec3);
	vec3.pop_back();
	printVec<type>(vec3);
	printValuesOf<type>(vec3);
}

template<typename type>
void	vecResizeReserveTest()
{
	P("Resize");
	ft::vector<type>	vec1;
	printVec(vec1);
	vec1.resize(10);
	printVec(vec1);
	vec1.push_back(generateVal<type>(6));
	vec1.push_back(generateVal<type>(6));
	vec1.push_back(generateVal<type>(6));
	vec1.push_back(generateVal<type>(6));
	vec1.push_back(generateVal<type>(6));
	vec1.push_back(generateVal<type>(6));
	vec1.resize(100);
	printVec(vec1);
	printValuesOf(vec1);
	// WIP errors in allocation o resolve ASAP
	// P("Reserve");
	// ft::vector<type>	vec2(vec1);
	// vec2.reserve(300);
	// printVec(vec2);
	// printValuesOf(vec2);
	// vec2.clear();
	// printVec(vec2);
	// printValuesOf(vec2);
	// vec2.reserve(50);
	// printVec(vec2);
	// printValuesOf(vec2);
}

template<typename type>
void	vecAssignTest()
{
	P("Asssign");
	ft::vector<type>	vec1;
	vec1.assign(50, generateVal<type>(10));
	printVec(vec1);
	printValuesOf(vec1);
}

template<typename type>
void	testVectorOf()
{
	// P(type);
	vecConstructorsTest<type>();
	P("---");
	vecPushPopTest<type>();
	P("---");
	vecResizeReserveTest<type>();
	P("---");
	vecAssignTest<type>();
	P("");
}

void	testVectors()
{
	P("Testing vectors");
	P("Int");
	testVectorOf<int>();
	P("");
	P("Char");
	testVectorOf<char>();
	P("");
	P("String");
	// testVectorOf<std::string>();
	P("");

}

int main()
{
	testVectors();
}