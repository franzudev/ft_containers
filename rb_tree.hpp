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
					node(key_type k, value_type v) : _pr(k, v), _parent(nullptr), _left(nullptr), _right(nullptr), _c(red) {};
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
				nodeptr tmp = root;
				while (tmp && tmp->key() != _k) {
					if (_k < tmp->key()) tmp = tmp->_left;
					if (_k > tmp->key()) tmp = tmp->_right;
				}
				if (tmp)
					return tmp;
				return nullptr;
			}

			void 		insert(key_type const & _k, value_type const & _v) {
				nodeptr ptr = new node(_k, _v);
				nodeptr	head = root;
				while (1) {
					if (_k < root->key() && root->_left) root = root->_left;
					else if (_k < root->key() && !root->_left) {
						root->_left = ptr;
						break ;
					}
					if (_k > root->key() && root->_right) root = root->_right;
					else if (_k > root->key() && !root->_right) {
						root->_right = ptr;
						break ;
					}
				}
				root = head;

			}
			void 		remove(key_type const & _k);

	}; // rb_tree

} // namespace ft
