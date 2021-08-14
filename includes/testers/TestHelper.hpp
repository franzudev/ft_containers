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
# include "../utils/iterator.hpp"
# include "../containers/vector.hpp"
# include "../containers/stack.hpp"
# include "../containers/map.hpp"
# include "../containers/set.hpp"
# include "../utils/is_integral.hpp"
# include "../utils/pair.hpp"
#endif

#include "../utils/Bureaucrat.hpp"
#include <iostream>
