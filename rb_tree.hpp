#pragma once

#include <iostream>
#include "pair.hpp"

namespace ft {

	template<class K, class T>
	class rb_tree {
		private:
			node *root;

			class node {

				public:
					typedef bool			color;
					typedef std::true_type 	red;
					typedef std::false_type black;

					node() : _c(red) {};
					~node() {};
					node(key_type k, value_type v) : _pr(k, v), _parent(nullptr), _left(nullptr), _right(nullptr) {};
					node(key_type k, value_type v, nodeptr * parent) : _pr(k, v), _parent(parent), _left(nullptr), _right(nullptr) {};
					node(nodeptr n) {this = n;}

					T&			value() {return _v;}
					T const &	value() const {return _v;}
					K&			key() {return _k;}
					K const &	key() const {return _k;}

				private:
					color							_c;
					ft::pair<key_type, value_type>	_pr;
					node							*_parent, *_left, *_right;
			}; // node

		public:

			typedef	T		value_type;
			typedef K		key_type;
			typedef node*	nodeptr;

			rb_tree() : root(NULL) {};

			node&		find(key_type const & _k) {
				if (!root || root->key() == _k)
					return root;
				if (_k < root->key()) root = root->_left;
				else if ()
			}
			void 		insert(key_type const & _k, value_type const & _v);
			void 		remove(key_type const & _k);

	}; // rb_tree

} // namespace ft
