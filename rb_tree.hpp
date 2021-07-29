#pragma once

#include <iostream>

namespace ft {

	template<class K, class T>
	class rb_tree {
		public:

			class node {

				public:
					typedef	node*			nodeptr;
					typedef	T				value_type;
					typedef K				key_type;
					typedef bool			color;
					typedef std::true_type 	red;
					typedef std::false_type black;

					node() {};
					~node() {};
					node(key_type k, value_type v) : _k(k), _v(v), _parent(nullptr), _left(nullptr), _right(nullptr) {};
					node(key_type k, value_type v, nodeptr * parent) : _k(k), _v(v), _parent(parent), _left(nullptr), _right(nullptr) {};
					node(nodeptr n) {this = n;}

					T&			value() {return _v;}
					T const &	value() const {return _v;}
					K&			key() {return _k;}
					K const &	key() const {return _k;}

				private:
					color		_c;
					key_type 	_k;
					value_type 	_v;
					node	*_parent, *_left, *_right;
			}; // node

			typedef	T						value_type;
			typedef K						key_type;
			typedef typename node::nodeptr	nodeptr;

			rb_tree() : root(NULL) {};

			node&		find(key_type const & _k) {
				if (!root || root->key() == _k)
					return root;
				if (_k < root->key()) root = root->_left;
				else if ()
			}
			const node&	find(key_type const & _k) const;
			void 		insert(key_type const & _k, value_type const & _v);
			void 		remove(key_type const & _k);

		private:
			node *root;


	}; // rb_tree

} // namespace ft
