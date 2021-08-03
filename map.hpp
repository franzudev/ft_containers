#pragma once

#include <map>
#include "enable_if.hpp"
#include "lexicographical_compare.hpp"
// TODO remove
#include "iterator.hpp"
#include "pair.hpp"

namespace ft {

	template < class Key, class T, class Compare = less<Key>, class Alloc = std::allocator<ft::pair<const Key,T> > >
	class map {
	public:
		// --- Definitions
		typedef Key                                     		key_type;
		typedef T                                       		mapped_type;
		typedef pair<const key_type, mapped_type>       		value_type;
		typedef Compare                                 		key_compare;
		typedef Allocator                               		allocator_type;
		typedef typename allocator_type::reference      		reference;
		typedef typename allocator_type::const_reference		const_reference;
		typedef typename allocator_type::pointer        		pointer;
		typedef typename allocator_type::const_pointer  		const_pointer;
		typedef typename allocator_type::size_type      		size_type;
		typedef typename allocator_type::difference_type		difference_type;

		typedef ft::iterator<ft::bidirectional_iterator_tag, T>	iterator;
		typedef ft::iterator<ft::bidirectional_iterator_tag, T> const_iterator;
		typedef std::reverse_iterator<iterator>         		reverse_iterator;
		typedef std::reverse_iterator<const_iterator>   		const_reverse_iterator;
		// definitions

		class value_compare: public binary_function<value_type, value_type, bool>
		{
			friend class map;
		protected:
			key_compare comp;

			value_compare(key_compare c);
		public:
			bool operator()(const value_type& x, const value_type& y) const;
		};

		// --- constructors
		map();
		explicit map( const Compare& comp, const Allocator& alloc = Allocator()) {}
		template< class InputIt > map( InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator()) {}
		map( const map& other ){}
		~map() {};
		// constructors

		// ---operators overload
		map& operator=( const map& other ) {}
		// operators overload

		// ---getters
		allocator_type get_allocator() const {}
		// getters

		// --- element access
		mapped_type& operator[](const key_type& k) {}

		mapped_type& at(const key_type& k) {}
		const mapped_type& at(const key_type& k) const {}
		// element access

		// --- iterators
		iterator begin() {}
		const_iterator begin() const {}
		iterator end() {}
		const_iterator end() const {}

		reverse_iterator rbegin() noexcept;
		const_reverse_iterator rbegin() const noexcept;
		reverse_iterator rend() noexcept;
		const_reverse_iterator rend()   const noexcept;
		// iterators

		// --- Capacity
		bool empty() const {}
		size_type size() const {}
		size_type max_size() const {}
		// capacity

		// --- modifiers
		void clear() {}
		ft::pair<iterator, bool> insert( const value_type& value ) {}
		iterator insert( iterator hint, const value_type& value ) {
			iterator(tree.insert(value));
		}
		template< class InputIt >
				void insert( InputIt first, InputIt last );
		void erase( iterator pos ) {}
		void erase( iterator first, iterator last ) {}
		size_type erase( const key_type& key ) {}
		void swap( map& other ) {}
		//

		// --- Lookup
		size_type count( const Key& key ) const {}
		iterator find( const Key& key ) {}
		const_iterator find( const Key& key ) const {}
		std::pair<iterator,iterator> equal_range( const Key& key ) {}
		std::pair<const_iterator,const_iterator> equal_range( const Key& key ) const {}
		iterator lower_bound( const Key& key ) {}
		const_iterator lower_bound( const Key& key ) const {}
		iterator upper_bound( const Key& key ) {}
		const_iterator upper_bound( const Key& key ) const {}
		//

		// --- Observers
		key_compare key_comp() const {}
		map::value_compare value_comp() const {}

	private:
		Tree	_tree;
	};
}
