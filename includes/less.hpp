#pragma once

namespace ft {
	template <class Pair>
	struct keyLess {
		bool operator ()(const Pair& p1, const Pair& p2) const {
			return p1 < p2;
		}
	};

	template <class InputIterator1, class InputIterator2>
	bool equal (InputIterator1 lit, InputIterator1 lend, InputIterator2 rit, InputIterator2 rend)
	{
		while (lit != lend)
		{
			if (rit == rend || *rit != *lit)
				return (false);
			++lit, ++rit;
		}

		return (rit == rend);
	}
}
