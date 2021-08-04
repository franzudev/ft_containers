#pragma once

#include <iostream>
#include "pair.hpp"

namespace ft {

	template<class K, class T>
	class rb_tree {

		private:
			enum color {BLACK, RED};

			class node {

				public:
					typedef bool			color;
					typedef std::true_type	red;
					typedef std::false_type	black;
					typedef	T				value_type;
					typedef K				key_type;
					typedef node*			nodeptr;

					node() : _c(RED) {};
					~node() {};
					node(key_type k, value_type v) : parent(nullptr), left(nullptr), right(nullptr), _c(RED),  _pr(ft::make_pair(k, v)) {};
					node(nodeptr n) {this = n;}

					T&			value() {return _pr.second;}
					T const &	value() const {return _pr.second;}
					K&			key() {return _pr.first;}
					K const &	key() const {return _pr.first;}
					void 		setColor(color nc) {_c = nc;}
					color		isRed() {return _c;}
					bool 		isLeft() {return this == parent->left;}
					bool 		isRight() {return this == parent->right;}
					nodeptr		uncle() {
						if (isLeft())
							return parent->right;
						return parent->left;
					}

					nodeptr							parent, left, right;
				private:
					color							_c;
					ft::pair<key_type, value_type>	_pr;
			}; // node

			node *root;

		public:
			typedef	T			value_type;
			typedef K			key_type;
			typedef node*		nodeptr;

		private:
			void	rightRotate(nodeptr parent, nodeptr gparent) {
				nodeptr buff = parent->right;
				parent->right = gparent;
				parent->parent = gparent->parent;
				gparent->left = buff;
				gparent->parent = parent;
			}

			void	leftRotate(nodeptr parent, nodeptr gparent) {
				nodeptr buff = parent->left;
				parent->left = gparent;
				parent->parent = gparent->parent;
				gparent->right = buff;
				gparent->parent = parent;
			}

			void	leftRightRotate(nodeptr child, nodeptr parent, nodeptr gparent) {
				child->left = parent;
				child->right = gparent;
				child->parent = gparent->parent;
				parent->parent = child;
				gparent->parent = child;
				parent->right = nullptr;
				gparent->left = nullptr;
			}

			void	rightLeftRotate(nodeptr child, nodeptr parent, nodeptr gparent) {
				child->right = parent;
				child->left = gparent;
				child->parent = gparent->parent;
				parent->parent = child;
				gparent->parent = child;
				parent->left = nullptr;
				gparent->right = nullptr;
			}

			void	balance(nodeptr ptr) {
				if (ptr == root) {
					ptr->setColor(BLACK);
					return ;
				}
				if (ptr->parent->isRed()) {
					if (ptr->uncle()->isRed()) {
						ptr->parent->setColor(BLACK);
						ptr->uncle()->setColor(BLACK);
						ptr->parent->parent->setColor(RED);
					}
					else {
						if (ptr->isLeft() && ptr->parent->isLeft())
							rightRotate(ptr->parent, ptr->parent->parent);
						if (ptr->isRight() && ptr->parent->isRight())
							leftRotate(ptr->parent, ptr->parent->parent);
						if (ptr->isLeft() && ptr->parent->isRight())
							rightLeftRotate(ptr, ptr->parent, ptr->parent->parent);
						if (ptr->isRight() && ptr->parent->isLeft())
							leftRightRotate(ptr, ptr->parent, ptr->parent->parent);
					}
				}
				balance(ptr->parent);
			}

		public:

			rb_tree() : root(NULL) {};

			nodeptr		find(key_type const & _k) {
				nodeptr tmp = root;
				while (tmp && tmp->key() != _k) {
					if (_k < tmp->key()) tmp = tmp->left;
					if (_k > tmp->key()) tmp = tmp->right;
				}
				if (tmp)
					return tmp;
				return nullptr;
			}

			void		insert(key_type const & _k, value_type const & _v) {
				nodeptr newnode = new node(_k, _v);
				if (!root) {
					root = newnode;
					root->setColor(BLACK);
					return ;
				}
				nodeptr	head = root;
				while (1) {
					if (_k < root->key() && root->left) root = root->left;
					else if (_k < root->key() && !root->left) {
						root->left = newnode;
						newnode->parent = root;
						break ;
					}
					if (_k > root->key() && root->right) root = root->right;
					else if (_k > root->key() && !root->right) {
						root->right = newnode;
						newnode->parent = root;
						break ;
					}
				}
				root = head;
				balance(newnode);
			}
			void 		remove(key_type const & _k);

	}; // rb_tree

} // namespace ft
