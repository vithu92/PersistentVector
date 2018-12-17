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
	typedef 
};