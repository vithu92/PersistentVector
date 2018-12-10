#include "RandomAccessFIle.h"


RandomAccessFile::RandomAccessFile(const string & filename) : m_fileName(filename)
{

	m_file.open(m_fileName.c_str(), ios::in | ios::out | ios::binary);

	if (!m_file) {
		//file doesn't exist
		m_file.clear(); //clear flags

		//create file and try to open again
		m_file.open(m_fileName.c_str(), ios::in | ios::out | ios::binary | ios::trunc);
		//dieser trunc sorgt dass falls diese File exisitert, wird diese Datei zurückgesetzt und falls nicht existiert, wird eine leere Datei erstellt
		if (!m_file) m_file.setf(ios::failbit);
	}
}

// return length in bytes
streamsize RandomAccessFile::length() const
{
	streampos curPos = m_file.tellg(); 
	
	m_file.seekg(0, ios::end); //seekg hat diverse Modi - hier wird die relative position gesucht.  => Zum Ende springen
	streampos length = m_file.tellg(); // Distanz zum Anfang ermitteln


	m_file.seekg(curPos);

	return length;
}

bool RandomAccessFile::truncate(streamsize s)
{
	return false;
}

