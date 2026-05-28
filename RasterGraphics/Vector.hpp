#pragma once
#include <iostream>
#include <stdexcept>
#include <cstddef>

template <class T>
class Vector {
private:
	T* m_arr;
	size_t m_size;
	size_t m_capacity;

	void copy(const Vector& other);
	void resizeCapacity();
	void free();

public:
	Vector();
	Vector(size_t n, const T& value = T());
	Vector(const Vector& other);
	Vector& operator=(const Vector& other);
	~Vector();

	class Iterator {
	private:
		T* m_curr;

	public:
		Iterator(T* curr);
		T& operator*();
		const T& operator*() const;
		Iterator operator++(int);
		Iterator& operator++();
		bool operator!=(const Iterator& other) const;
		bool operator==(const Iterator& other) const;
	};

	class ConstIterator {
	private:
		const T* m_curr;

	public:

		ConstIterator(const T* curr);
		const T& operator*() const;
		ConstIterator& operator++();
		ConstIterator operator++(int);
		bool operator!=(const ConstIterator& other) const;
		bool operator==(const ConstIterator& other) const;
	};

	using iterator = Iterator;
	using const_iterator = ConstIterator;
	iterator begin();
	iterator end();
	const_iterator begin() const;
	const_iterator end() const;

	bool empty() const;
	operator bool() const;
	size_t size() const;
	
	void resize(size_t count, const T& val);
	void push_back(const T& el);
	void pop_back();
	T& operator[](size_t index);
	const T& operator[](size_t index) const;
	T& at(size_t index);
	const T& at(size_t index) const;
	void clear();
};

template <class T>
void Vector<T>::copy(const Vector& other) {
	m_capacity = other.m_capacity;
	m_size = other.m_size;
	m_arr = new T[other.m_capacity];

	for (size_t i = 0; i < m_size; i++) {
		m_arr[i] = other.m_arr[i];
	}
}

template <class T>
void Vector<T>::free() {
	delete[] m_arr;
	m_arr = nullptr;
	m_size = 0;
	m_capacity = 0;
}

template <class T>
void Vector<T>::resizeCapacity() {
	size_t newCapacity;
	if (m_capacity == 0) {
		newCapacity = 1;
	}
	else {
		newCapacity = 2 * m_capacity;
	}

	T* newArr = new T[newCapacity];

	for (size_t i = 0; i < m_size; i++) {
		newArr[i] = m_arr[i];
	}

	delete[] m_arr;
	m_arr = newArr;
	m_capacity = newCapacity;
}

template <class T>
Vector<T>::Vector() : m_arr(nullptr), m_size(0), m_capacity(0) {}

template<class T>
Vector<T>::Vector(size_t n, const T& value) : m_size(n), m_capacity(n) {
	m_arr = new T[m_capacity];
	for (size_t i = 0; i < m_size; i++) {
		m_arr[i] = value;
	}
}
template <class T>
Vector<T>::Vector(const Vector& other) {
	copy(other);
}

template <class T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
	if (this != &other) {
		free();
		copy(other);
	}

	return *this;
}

template <class T>
Vector<T>::~Vector() {
	free();
}

template<class T>
Vector<T>::Iterator::Iterator(T* curr) : m_curr(curr) {}

template<class T>
T& Vector<T>::Iterator::operator*() {
	return *m_curr;
}

template <class T>
const T& Vector<T>::Iterator::operator*() const {
	return *m_curr;
}

template <class T>
typename Vector<T>::Iterator& Vector<T>::Iterator::operator++() {
	++m_curr;
	return *this;
}

template <class T>
typename Vector<T>::Iterator Vector<T>::Iterator::operator++(int) {
	Iterator temp = *this;
	++m_curr;
	return temp;
}

template <class T>
bool Vector<T>::Iterator::operator!=(const Iterator& other) const {
	return (this->m_curr != other.m_curr);
}

template <class T>
bool Vector<T>::Iterator::operator==(const Iterator& other) const {
	return (this->m_curr == other.m_curr);
}
//
template <class T>
Vector<T>::ConstIterator::ConstIterator(const T* curr) : m_curr(curr) {}

template<class T>
const T& Vector<T>::ConstIterator::operator*() const {
	return *m_curr;
}

template <class T>
typename Vector<T>::ConstIterator& Vector<T>::ConstIterator::operator++() {
	++m_curr;
	return *this;
}

template <class T>
typename Vector<T>::ConstIterator Vector<T>::ConstIterator::operator++(int) {
	ConstIterator temp = *this;
	++m_curr;
	return temp;
}

template <class T>
bool Vector<T>::ConstIterator::operator!=(const ConstIterator& other) const {
	return (this->m_curr != other.m_curr);
}

template <class T>
bool Vector<T>::ConstIterator::operator==(const ConstIterator& other) const {
	return (this->m_curr == other.m_curr);
}

template <class T>
typename Vector<T>::iterator Vector<T>::begin() {
	return Iterator(m_arr);
}

template <class T>
typename Vector<T>::iterator Vector<T>::end() {
	return Iterator(m_arr + m_size);
}

template <class T>
typename Vector<T>::const_iterator Vector<T>::begin() const {

	return ConstIterator(m_arr);
}

template <class T>
typename Vector<T>::const_iterator Vector<T>::end() const {

	return ConstIterator(m_arr + m_size);
}


template<class T>
bool Vector<T>::empty() const {
	return m_size == 0;
}

template<class T>
Vector<T>::operator bool() const {
	return !empty();
}

template<class T>
size_t Vector<T>::size() const {
	return m_size;
}

template<class T>
void Vector<T>::resize(size_t count, const T& val) {
	if (count > m_capacity) {
		size_t newCapacity = (m_capacity == 0) ? 1 : m_capacity;

		while (newCapacity < count) {
			newCapacity *= 2;
		}

 		T* newArr = new T[newCapacity];

		for (size_t i = 0; i < m_size; i++) {
			newArr[i] = m_arr[i];
		}

		delete[] m_arr;
		m_arr = newArr;
		m_capacity = newCapacity;
	}

	if (count > m_size) {
		for (size_t i = m_size; i < count; i++) {
			m_arr[i] = val;
		}
	}

	m_size = count;
}

template<class T>
void Vector<T>::push_back(const T& el) {
	if (m_capacity <= m_size)
	{
		resizeCapacity();
	}

	m_arr[m_size++] = el;
}

template<class T>
void Vector<T>::pop_back() {
	if (m_size == 0) {
		throw std::out_of_range("Vector is empty!");
	}

	--m_size;
}

template<class T>
T& Vector<T>::operator[] (size_t index) {
	return m_arr[index];
}

template<class T>
const T& Vector<T>::operator[] (size_t index) const {
	return m_arr[index];
}

template<class T>
T& Vector<T>::at(size_t index) {
	if (index >= m_size) {
		throw std::out_of_range("Index out of range!");
	}
	
	return m_arr[index];
}

template<class T>
const T& Vector<T>::at(size_t index) const {
	if (index >= m_size) {
		throw std::out_of_range("Index out of range!");
	}

	return m_arr[index];
}

template<class T>
void Vector<T>::clear() {
	m_size = 0;
}