#pragma once
// prototype

template<class T> class PersistentVector;

template<class T> class VectorIterator {
	friend class PersistentVector<T>;
	PersistentVector<T> *m_vector; //muss ein Zeiger sein, weil PerisistentVektor nur ein Protoype ist und nicht die eigentliche Vektor
	size_t m_pos; // aktuelle Zugriffsposition

	VectorIterator(PersistentVector<T> *vector, size_t pos) :m_vector(vector), m_pos(pos) {}
	
public:
	typedef random_access_iterator_tag iterator_catagory;
	typedef T value_type;
	typedef int _w64 difference_type;
	typedef T* pointer;
	typedef T& reference;
	typedef const T& const_reference;
	typedef typename PersistentVector<T>::accessor accessor;

	VectorIterator& operator=(const VectorIterator& it) {
		if (this != &it) {
			m_vector = it.m_vector;
			m_pos = it.m_pos;
		}
		return *this;
	}

	// relational Operators

	// increment and decrement operator

	// arithmetische operators

	// access operators

	//schreibrecht
	access operator*() {
		return (*m_vector)[m_pos];
	}

	//ohne schreibrecht
	T operator*() const {
		return m_vector[m_pos];
	}

	//index operator
	accessor operator[](size_t delta) {
		return (*m_vector)[m_pos + delta];
	}

	T operator[](size_t delta) const {
		return (*m_vector)[m_pos + delta];
	}
};