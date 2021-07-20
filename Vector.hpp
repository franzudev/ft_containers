#pragma once

#include <memory>
#include <algorithm>
#include <Iterator.hpp>

namespace ft {
	template <class T, class Allocator = std::allocator<T> >
	class vector {
	public:
		vector() {

		}
		~vector();
		vector(vector<T> const &);
		vector<T> &operator=(vector<T> const &);

		typedef typename T									value_type;
		typedef typename Allocator							allocator_type;
		typedef typename allocator_type::reference			reference;
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;
		typedef typename iterator_traits<T>					iterator;
		typedef typename const iterator_traits<T>			const_iterator;

	};
}
