#pragma once
#include "RandomAccessFile.h"
#include "VectorAccessor.hpp"
#include <assert.h>

template<class T>
class PersistentVector {
	friend class VectorAccessor<T>;

	RandomAccessFile m_file; // zur Speicherung von Elementen des Typs T
	size_t m_size;		// Anzahl Elemente im Vektor

public:

	typedef T value_type;
	typedef T& reference;
	typedef const T& const_reference;
	typedef VectorAccessor<T> accessor;


	PersistentVector(const string& filename) : m_file{ filename }, m_size( capacity() ) {}

	//dtor
	virtual ~PersistentVector() {
		size_t cap = capacity();
		assert(m_size <= cap);
		if (m_size < cap) m_file.truncate(m_size * sizeof(T));
	}

	size_t capacity() const {
		return (size_t)(m_file.length() / sizeof(T));
	}

	size_t size() const { 
		return m_size;
	}

	bool empty() const {
		return m_size == 0; 
	}

	value_type operator[] (size_t pos) const {
		return read(pos);
	}

	accessor operator[](size_t pos) {
		return at(pos);
	}

	accessor front() {
		return at(0);
	}

	accessor back() {
		return at(size() - 1);
	}

	void push_back(const_reference val) {
		write(m_size++, val);
	}

	void pop_back() {
		if (m_size < 1) throw RandomAccessFile::IOException("bad size");
		m_size--;
	}

	void assign(size_t m_size, const_reference val) {
		clear();
		m_size = size();
		for (size_t i = 0; i < m_size; i++) {
			m_file.write(val);
		}
	}
	
	void clear() { 
		if (!m_file.truncate(0)) throw RandomAccessFile::IOException("truncation error");
		m_size = 0;
	}

private:
	value_type read(size_t pos) const {
		return m_file.read<T>(pos*sizeof(T));
	}

	void write(size_t pos, const_reference val) {
		m_file.write(val, pos * sizeof(T));
	}

	accessor at(size_t pos) {
		if (pos >= m_size) throw RandomAccessFile::IOException("bad position");
		return VectorAccessor<T>(this, pos);
	}
};