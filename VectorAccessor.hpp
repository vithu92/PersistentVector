#pragma once

//prototype um nicht eine zyklische abhänigkeit zu haben
template<class T> class PersistentVector;

template < class T> class VectorAccessor{
	friend class PersistentVector<T>; // PerisistentVecotr darf auf private Attribute/Methoden zugreifen
	PersistentVector<T> *m_vector; //muss ein Zeiger sein, weil PerisistentVektor nur ein Protoype ist und nicht die eigentliche Vektor
	size_t m_pos; // aktuelle Zugriffsposition
	T m_value; // Wert an der aktuellen Position

	VectorAccessor(PersistentVector<T> *vector, size_t pos) :m_vector(vector), m_pos(pos) {}
public:
	VectorAccessor(const VectorAccessor& va) : m_vector(nullptr), m_pos(-1), m_value(va) 
	{}

	operator T() const {
		if (m_vector) {
			return m_vector->read(m_pos);
		}
		else {
			return m_value;
		}
	}

	VectorAccessor& operator=(const VectorAccessor& val) {
		if (m_vector) {
			m_vector->write(m_pos, val);
		}
		else {
			m_value = val;
		}
		return *this;
	}

	
};