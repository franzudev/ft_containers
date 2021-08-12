#pragma once

#define TEST_ARR_SIZE 10

#ifdef USE_STL
# define STL "std: "
# include <iterator>
# include <vector>
# include <stack>
# include <array>
# include <map>
# include <set>
namespace ft = std;
#else
# define STL "ft: "
# include "iterator.hpp"
# include "vector.hpp"
# include "stack.hpp"
# include "map.hpp"
# include "set.hpp"
# include "is_integral.hpp"
#endif

#include "Bureaucrat.hpp"
#include <iostream>
