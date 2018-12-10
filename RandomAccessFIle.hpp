#pragma once

#include "RandomAccessFile.h"

template<class T>
inline T RandomAccessFile::read(streampos pos /* = -1*/) const
{
	if (pos >= 0) {
		// random access
		m_file.seekg(pos);
		if (!m_file) throw IOException("read error");
	}

	T data;

	m_file.read((char*)&data, sizeof(T)); //adresse des Data-Objects ud wieviel gelesen werden kann - > hier so gross wie T size ist. Casten auf char damit es gelese nwerden kann
	if (!m_file) throw IOException("read error");
	
	return data;
}

template<class T>
inline void RandomAccessFile::write(const T & data, streampos pos /* = -1*/)
{
	if (pos >= 0) {
		m_file.seekp(pos);
		if (!m_file) throw IOException("write error");
	}

	m_file.write((char*)&data, sizeof(T));
	if (!m_file) throw IOException("write error");
}