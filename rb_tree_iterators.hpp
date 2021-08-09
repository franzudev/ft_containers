#pragma once

#include "iterator.hpp"

namespace ft {

	template<class Node>
	struct rb_tree_iterator: ft::iterator<ft::bidirectional_iterator_tag, Node> {
		typedef Node 						*iterator_type;
		typedef typename Node::value_type	value_type;

	private:
		iterator_type m_ptr;

	public:

		explicit rb_tree_iterator() : m_ptr(nullptr) {};

		explicit rb_tree_iterator(iterator_type ptr) : m_ptr(ptr) {}

		rb_tree_iterator(rb_tree_iterator const &other) { *this = other; }

		template<class Iter>
		rb_tree_iterator &operator=(Iter const &other) {
			m_ptr = other.base();
			return *this;
		}

		value_type operator*() const {
			return m_ptr->data;
		}

		value_type *operator->() const {
			return &m_ptr->data;
		}

		// Prefix increment
		rb_tree_iterator &operator++() {
			if (m_ptr->right)
			{
				m_ptr = m_ptr->right;
				if (m_ptr->bound || (m_ptr->left && m_ptr->left->bound))
					return *this;
				while (m_ptr->left)
					m_ptr = m_ptr->left;
			}
			else if (m_ptr->isLeft())
			{
				m_ptr = m_ptr->parent;
			}
			else
			{
				while (m_ptr->parent && !m_ptr->parent->bound && !m_ptr->isLeft())
					m_ptr = m_ptr->parent;
				m_ptr = m_ptr->parent;
			}
			return *this;
		}

		// Postfix increment
		rb_tree_iterator operator++(int) {
			rb_tree_iterator tmp = *this;
			++*this;
			return tmp;
		}

		// Prefix decrement
		rb_tree_iterator &operator--() {
			if (m_ptr->left)
			{
				m_ptr = m_ptr->left;
				if (m_ptr->bound || (m_ptr->right && m_ptr->right->bound))
					return *this;
				while (m_ptr->right)
					m_ptr = m_ptr->right;
			}
			else if (m_ptr->isRight())
			{
				m_ptr = m_ptr->parent;
			}
			else
			{
				while (m_ptr->parent && !m_ptr->parent->bound && !m_ptr->isRight())
					m_ptr = m_ptr->parent;
				m_ptr = m_ptr->parent;
			}
			return *this;
		}

		// Postfix decrement
		rb_tree_iterator operator--(int) {
			rb_tree_iterator tmp = *this;
			--*this;
			return tmp;
		}

		iterator_type base() {
			return m_ptr;
		}

		const iterator_type base() const {
			return m_ptr;
		}

		bool operator==(const rb_tree_iterator &rhs) {
			return m_ptr == rhs.m_ptr;
		}

		bool operator!=(const rb_tree_iterator &rhs) {
			return m_ptr != rhs.m_ptr;
		}
	};

	template<class Node>
	struct const_rb_tree_iterator: ft::iterator<ft::bidirectional_iterator_tag, Node> {
		typedef Node 						*iterator_type;
		typedef typename Node::value_type	value_type;

		explicit const_rb_tree_iterator() : m_ptr(nullptr) {};

		explicit const_rb_tree_iterator(iterator_type ptr) : m_ptr(ptr) {
		}

		template<class Iter>
		const_rb_tree_iterator(Iter const &other) {
			*this = other;
		}

		const value_type operator*() const {
			return m_ptr->data;
		}

		const value_type *operator->() const {
			return &m_ptr->data;
		}

		// Prefix increment
		const_rb_tree_iterator &operator++() {
			if (m_ptr->right)
			{
				m_ptr = m_ptr->right;
				if (m_ptr->bound || (m_ptr->left && m_ptr->left->bound))
					return *this;
				while (m_ptr->left)
					m_ptr = m_ptr->left;
			}
			else if (m_ptr->isLeft())
			{
				m_ptr = m_ptr->parent;
			}
			else
			{
				while (m_ptr->parent && !m_ptr->bound && !m_ptr->isLeft())
					m_ptr = m_ptr->parent;
				m_ptr = m_ptr->parent;
			}
			return *this;
		}

		// Postfix increment
		const_rb_tree_iterator operator++(int) {
			const_rb_tree_iterator tmp = *this;
			++*this;
			return tmp;
		}

		// Prefix decrement
		const_rb_tree_iterator &operator--() {
			if (m_ptr->left)
			{
				m_ptr = m_ptr->left;
				if (m_ptr->bound || (m_ptr->right && m_ptr->right->bound))
					return *this;
				while (m_ptr->right)
					m_ptr = m_ptr->right;
			}
			else if (m_ptr->isRight())
			{
				m_ptr = m_ptr->parent;
			}
			else
			{
				while (m_ptr->parent && !m_ptr->parent->bound && !m_ptr->isRight())
					m_ptr = m_ptr->parent;
				m_ptr = m_ptr->parent;
			}
			return *this;
		}

		// Postfix decrement
		const_rb_tree_iterator operator--(int) {
			const_rb_tree_iterator tmp = *this;
			--*this;
			return tmp;
		}

		const iterator_type base() {
			return m_ptr;
		}

		const iterator_type base() const {
			return m_ptr;
		}

		template<class Iter>
		const_rb_tree_iterator &operator=(Iter const &other) {
			m_ptr = other.base();
			return *this;
		}

		bool operator==(const const_rb_tree_iterator &rhs) {
			return m_ptr == rhs.m_ptr;
		}

		bool operator!=(const const_rb_tree_iterator &rhs) {
			return m_ptr != rhs.m_ptr;
		}

	private:
		iterator_type m_ptr;
	};
}